#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int uc_flags; } ;
typedef  TYPE_1__ ucontext_t ;

/* Variables and functions */
 int UC_SIGCONTEXT_SS ; 
 int UC_STRICT_RESTORE_SS ; 
 int cs_bitness (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * csptr (TYPE_1__*) ; 
 scalar_t__ is_valid_ss (unsigned short) ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned short* ssptr (TYPE_1__*) ; 

__attribute__((used)) static void validate_signal_ss(int sig, ucontext_t *ctx)
{
#ifdef __x86_64__
	bool was_64bit = (cs_bitness(*csptr(ctx)) == 64);

	if (!(ctx->uc_flags & UC_SIGCONTEXT_SS)) {
		printf("[FAIL]\tUC_SIGCONTEXT_SS was not set\n");
		nerrs++;

		/*
		 * This happens on Linux 4.1.  The rest will fail, too, so
		 * return now to reduce the noise.
		 */
		return;
	}

	/* UC_STRICT_RESTORE_SS is set iff we came from 64-bit mode. */
	if (!!(ctx->uc_flags & UC_STRICT_RESTORE_SS) != was_64bit) {
		printf("[FAIL]\tUC_STRICT_RESTORE_SS was wrong in signal %d\n",
		       sig);
		nerrs++;
	}

	if (is_valid_ss(*ssptr(ctx))) {
		/*
		 * DOSEMU was written before 64-bit sigcontext had SS, and
		 * it tries to figure out the signal source SS by looking at
		 * the physical register.  Make sure that keeps working.
		 */
		unsigned short hw_ss;
		asm ("mov %%ss, %0" : "=rm" (hw_ss));
		if (hw_ss != *ssptr(ctx)) {
			printf("[FAIL]\tHW SS didn't match saved SS\n");
			nerrs++;
		}
	}
#endif
}