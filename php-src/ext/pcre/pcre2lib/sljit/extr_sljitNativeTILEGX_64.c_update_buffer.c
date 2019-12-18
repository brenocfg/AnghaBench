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
typedef  int /*<<< orphan*/  tilegx_bundle_bits ;
struct sljit_compiler {int dummy; } ;
struct jit_instr {int line; } ;
typedef  int /*<<< orphan*/  sljit_s32 ;

/* Variables and functions */
 int /*<<< orphan*/  SLJIT_UNREACHABLE () ; 
 scalar_t__ assign_pipes () ; 
 int /*<<< orphan*/  get_bundle_bit (struct jit_instr*) ; 
 struct jit_instr* inst_buf ; 
 int inst_buf_index ; 
 int /*<<< orphan*/  print_insn_tilegx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  push_inst (struct sljit_compiler*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_inst_nodebug (struct sljit_compiler*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sljit_s32 update_buffer(struct sljit_compiler *compiler)
{
	int i;
	int orig_index = inst_buf_index;
	struct jit_instr inst0 = inst_buf[0];
	struct jit_instr inst1 = inst_buf[1];
	struct jit_instr inst2 = inst_buf[2];
	tilegx_bundle_bits bits = 0;

	/* If the bundle is valid as is, perform the encoding and return 1. */
	if (assign_pipes() == 0) {
		for (i = 0; i < inst_buf_index; i++) {
			bits |= get_bundle_bit(inst_buf + i);
#ifdef TILEGX_JIT_DEBUG
			printf("|%04d", inst_buf[i].line);
#endif
		}
#ifdef TILEGX_JIT_DEBUG
		if (inst_buf_index == 3)
			printf("|M0|:\t");
		else
			printf("|M0|:\t\t");
		print_insn_tilegx(&bits);
#endif

		inst_buf_index = 0;

#ifdef TILEGX_JIT_DEBUG
		return push_inst_nodebug(compiler, bits);
#else
		return push_inst(compiler, bits);
#endif
	}

	/* If the bundle is invalid, split it in two. First encode the first two
	   (or possibly 1) instructions, and then the last, separately. Note that
	   assign_pipes may have re-ordered the instrs (by inserting no-ops in
	   lower slots) so we need to reset them. */

	inst_buf_index = orig_index - 1;
	inst_buf[0] = inst0;
	inst_buf[1] = inst1;
	inst_buf[2] = inst2;
	if (assign_pipes() == 0) {
		for (i = 0; i < inst_buf_index; i++) {
			bits |= get_bundle_bit(inst_buf + i);
#ifdef TILEGX_JIT_DEBUG
			printf("|%04d", inst_buf[i].line);
#endif
		}

#ifdef TILEGX_JIT_DEBUG
		if (inst_buf_index == 3)
			printf("|M1|:\t");
		else
			printf("|M1|:\t\t");
		print_insn_tilegx(&bits);
#endif

		if ((orig_index - 1) == 2) {
			inst_buf[0] = inst2;
			inst_buf_index = 1;
		} else if ((orig_index - 1) == 1) {
			inst_buf[0] = inst1;
			inst_buf_index = 1;
		} else
			SLJIT_UNREACHABLE();

#ifdef TILEGX_JIT_DEBUG
		return push_inst_nodebug(compiler, bits);
#else
		return push_inst(compiler, bits);
#endif
	} else {
		/* We had 3 instrs of which the first 2 can't live in the same bundle.
		   Split those two. Note that we don't try to then combine the second
		   and third instr into a single bundle.  First instruction: */
		inst_buf_index = 1;
		inst_buf[0] = inst0;
		inst_buf[1] = inst1;
		inst_buf[2] = inst2;
		if (assign_pipes() == 0) {
			for (i = 0; i < inst_buf_index; i++) {
				bits |= get_bundle_bit(inst_buf + i);
#ifdef TILEGX_JIT_DEBUG
				printf("|%04d", inst_buf[i].line);
#endif
			}

#ifdef TILEGX_JIT_DEBUG
			if (inst_buf_index == 3)
				printf("|M2|:\t");
			else
				printf("|M2|:\t\t");
			print_insn_tilegx(&bits);
#endif

			inst_buf[0] = inst1;
			inst_buf[1] = inst2;
			inst_buf_index = orig_index - 1;
#ifdef TILEGX_JIT_DEBUG
			return push_inst_nodebug(compiler, bits);
#else
			return push_inst(compiler, bits);
#endif
		} else
			SLJIT_UNREACHABLE();
	}

	SLJIT_UNREACHABLE();
}