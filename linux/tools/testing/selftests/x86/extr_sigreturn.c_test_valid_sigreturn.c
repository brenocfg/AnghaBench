#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct selectors {int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; } ;
typedef  int greg_t ;

/* Variables and functions */
 int NGREG ; 
 int REG_CSGSFS ; 
 int REG_CX ; 
 int REG_IP ; 
 int REG_SP ; 
 int REG_TRAPNO ; 
 int REG_UESP ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int data16_sel ; 
 int find_cs (int) ; 
 scalar_t__ nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 int* requested_regs ; 
 int* resulting_regs ; 
 int sig_cs ; 
 int sig_ss ; 

__attribute__((used)) static int test_valid_sigreturn(int cs_bits, bool use_16bit_ss, int force_ss)
{
	int cs = find_cs(cs_bits);
	if (cs == -1) {
		printf("[SKIP]\tCode segment unavailable for %d-bit CS, %d-bit SS\n",
		       cs_bits, use_16bit_ss ? 16 : 32);
		return 0;
	}

	if (force_ss != -1) {
		sig_ss = force_ss;
	} else {
		if (use_16bit_ss) {
			if (!data16_sel) {
				printf("[SKIP]\tData segment unavailable for %d-bit CS, 16-bit SS\n",
				       cs_bits);
				return 0;
			}
			sig_ss = data16_sel;
		} else {
			asm volatile ("mov %%ss,%0" : "=r" (sig_ss));
		}
	}

	sig_cs = cs;

	printf("[RUN]\tValid sigreturn: %d-bit CS (%hx), %d-bit SS (%hx%s)\n",
	       cs_bits, sig_cs, use_16bit_ss ? 16 : 32, sig_ss,
	       (sig_ss & 4) ? "" : ", GDT");

	raise(SIGUSR1);

	nerrs = 0;

	/*
	 * Check that each register had an acceptable value when the
	 * int3 trampoline was invoked.
	 */
	for (int i = 0; i < NGREG; i++) {
		greg_t req = requested_regs[i], res = resulting_regs[i];

		if (i == REG_TRAPNO || i == REG_IP)
			continue;	/* don't care */

		if (i == REG_SP) {
			/*
			 * If we were using a 16-bit stack segment, then
			 * the kernel is a bit stuck: IRET only restores
			 * the low 16 bits of ESP/RSP if SS is 16-bit.
			 * The kernel uses a hack to restore bits 31:16,
			 * but that hack doesn't help with bits 63:32.
			 * On Intel CPUs, bits 63:32 end up zeroed, and, on
			 * AMD CPUs, they leak the high bits of the kernel
			 * espfix64 stack pointer.  There's very little that
			 * the kernel can do about it.
			 *
			 * Similarly, if we are returning to a 32-bit context,
			 * the CPU will often lose the high 32 bits of RSP.
			 */

			if (res == req)
				continue;

			if (cs_bits != 64 && ((res ^ req) & 0xFFFFFFFF) == 0) {
				printf("[NOTE]\tSP: %llx -> %llx\n",
				       (unsigned long long)req,
				       (unsigned long long)res);
				continue;
			}

			printf("[FAIL]\tSP mismatch: requested 0x%llx; got 0x%llx\n",
			       (unsigned long long)requested_regs[i],
			       (unsigned long long)resulting_regs[i]);
			nerrs++;
			continue;
		}

		bool ignore_reg = false;
#if __i386__
		if (i == REG_UESP)
			ignore_reg = true;
#else
		if (i == REG_CSGSFS) {
			struct selectors *req_sels =
				(void *)&requested_regs[REG_CSGSFS];
			struct selectors *res_sels =
				(void *)&resulting_regs[REG_CSGSFS];
			if (req_sels->cs != res_sels->cs) {
				printf("[FAIL]\tCS mismatch: requested 0x%hx; got 0x%hx\n",
				       req_sels->cs, res_sels->cs);
				nerrs++;
			}

			if (req_sels->ss != res_sels->ss) {
				printf("[FAIL]\tSS mismatch: requested 0x%hx; got 0x%hx\n",
				       req_sels->ss, res_sels->ss);
				nerrs++;
			}

			continue;
		}
#endif

		/* Sanity check on the kernel */
		if (i == REG_CX && req != res) {
			printf("[FAIL]\tCX (saved SP) mismatch: requested 0x%llx; got 0x%llx\n",
			       (unsigned long long)req,
			       (unsigned long long)res);
			nerrs++;
			continue;
		}

		if (req != res && !ignore_reg) {
			printf("[FAIL]\tReg %d mismatch: requested 0x%llx; got 0x%llx\n",
			       i, (unsigned long long)req,
			       (unsigned long long)res);
			nerrs++;
		}
	}

	if (nerrs == 0)
		printf("[OK]\tall registers okay\n");

	return nerrs;
}