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
struct probe_trace_arg_ref {struct probe_trace_arg_ref* next; int /*<<< orphan*/  offset; } ;
struct probe_trace_arg {char* value; struct probe_trace_arg_ref* ref; } ;
struct bpf_insn_pos {struct bpf_insn* pos; struct bpf_insn* end; struct bpf_insn* begin; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ALU64_IMM (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  BPF_JA ; 
 int /*<<< orphan*/  BPF_JMP_IMM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BPF_LOADER_ERRNO__PROLOGUEOOB ; 
 size_t BPF_MAXINSNS ; 
 int /*<<< orphan*/  BPF_MOV ; 
 int /*<<< orphan*/  BPF_MOV64_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BPF_PROLOGUE_FETCH_RESULT_REG ; 
 int BPF_PROLOGUE_MAX_ARGS ; 
 scalar_t__ BPF_PROLOGUE_START_ARG_REG ; 
 int /*<<< orphan*/  BPF_REG_0 ; 
 int /*<<< orphan*/  BPF_REG_ARG1 ; 
 int /*<<< orphan*/  BPF_REG_CTX ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int /*<<< orphan*/  JMP_TO_USER_CODE ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 int /*<<< orphan*/  OFFSET_MIN ; 
 int check_pos (struct bpf_insn_pos*) ; 
 int gen_prologue_fastpath (struct bpf_insn_pos*,struct probe_trace_arg*,int) ; 
 int gen_prologue_slowpath (struct bpf_insn_pos*,struct probe_trace_arg*,int) ; 
 int /*<<< orphan*/  ins (int /*<<< orphan*/ ,struct bpf_insn_pos*) ; 
 size_t pos_get_cnt (struct bpf_insn_pos*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,char*,...) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int prologue_relocate (struct bpf_insn_pos*,struct bpf_insn*,struct bpf_insn*,struct bpf_insn*) ; 

int bpf__gen_prologue(struct probe_trace_arg *args, int nargs,
		      struct bpf_insn *new_prog, size_t *new_cnt,
		      size_t cnt_space)
{
	struct bpf_insn *success_code = NULL;
	struct bpf_insn *error_code = NULL;
	struct bpf_insn *user_code = NULL;
	struct bpf_insn_pos pos;
	bool fastpath = true;
	int err = 0, i;

	if (!new_prog || !new_cnt)
		return -EINVAL;

	if (cnt_space > BPF_MAXINSNS)
		cnt_space = BPF_MAXINSNS;

	pos.begin = new_prog;
	pos.end = new_prog + cnt_space;
	pos.pos = new_prog;

	if (!nargs) {
		ins(BPF_ALU64_IMM(BPF_MOV, BPF_PROLOGUE_FETCH_RESULT_REG, 0),
		    &pos);

		if (check_pos(&pos))
			goto errout;

		*new_cnt = pos_get_cnt(&pos);
		return 0;
	}

	if (nargs > BPF_PROLOGUE_MAX_ARGS) {
		pr_warning("bpf: prologue: %d arguments are dropped\n",
			   nargs - BPF_PROLOGUE_MAX_ARGS);
		nargs = BPF_PROLOGUE_MAX_ARGS;
	}

	/* First pass: validation */
	for (i = 0; i < nargs; i++) {
		struct probe_trace_arg_ref *ref = args[i].ref;

		if (args[i].value[0] == '@') {
			/* TODO: fetch global variable */
			pr_err("bpf: prologue: global %s%+ld not support\n",
				args[i].value, ref ? ref->offset : 0);
			return -ENOTSUP;
		}

		while (ref) {
			/* fastpath is true if all args has ref == NULL */
			fastpath = false;

			/*
			 * Instruction encodes immediate value using
			 * s32, ref->offset is long. On systems which
			 * can't fill long in s32, refuse to process if
			 * ref->offset too large (or small).
			 */
#ifdef __LP64__
#define OFFSET_MAX	((1LL << 31) - 1)
#define OFFSET_MIN	((1LL << 31) * -1)
			if (ref->offset > OFFSET_MAX ||
					ref->offset < OFFSET_MIN) {
				pr_err("bpf: prologue: offset out of bound: %ld\n",
				       ref->offset);
				return -BPF_LOADER_ERRNO__PROLOGUEOOB;
			}
#endif
			ref = ref->next;
		}
	}
	pr_debug("prologue: pass validation\n");

	if (fastpath) {
		/* If all variables are registers... */
		pr_debug("prologue: fast path\n");
		err = gen_prologue_fastpath(&pos, args, nargs);
		if (err)
			goto errout;
	} else {
		pr_debug("prologue: slow path\n");

		/* Initialization: move ctx to a callee saved register. */
		ins(BPF_MOV64_REG(BPF_REG_CTX, BPF_REG_ARG1), &pos);

		err = gen_prologue_slowpath(&pos, args, nargs);
		if (err)
			goto errout;
		/*
		 * start of ERROR_CODE (only slow pass needs error code)
		 *   mov r2 <- 1  // r2 is error number
		 *   mov r3 <- 0  // r3, r4... should be touched or
		 *                // verifier would complain
		 *   mov r4 <- 0
		 *   ...
		 *   goto usercode
		 */
		error_code = pos.pos;
		ins(BPF_ALU64_IMM(BPF_MOV, BPF_PROLOGUE_FETCH_RESULT_REG, 1),
		    &pos);

		for (i = 0; i < nargs; i++)
			ins(BPF_ALU64_IMM(BPF_MOV,
					  BPF_PROLOGUE_START_ARG_REG + i,
					  0),
			    &pos);
		ins(BPF_JMP_IMM(BPF_JA, BPF_REG_0, 0, JMP_TO_USER_CODE),
				&pos);
	}

	/*
	 * start of SUCCESS_CODE:
	 *   mov r2 <- 0
	 *   goto usercode  // skip
	 */
	success_code = pos.pos;
	ins(BPF_ALU64_IMM(BPF_MOV, BPF_PROLOGUE_FETCH_RESULT_REG, 0), &pos);

	/*
	 * start of USER_CODE:
	 *   Restore ctx to r1
	 */
	user_code = pos.pos;
	if (!fastpath) {
		/*
		 * Only slow path needs restoring of ctx. In fast path,
		 * register are loaded directly from r1.
		 */
		ins(BPF_MOV64_REG(BPF_REG_ARG1, BPF_REG_CTX), &pos);
		err = prologue_relocate(&pos, error_code, success_code,
					user_code);
		if (err)
			goto errout;
	}

	err = check_pos(&pos);
	if (err)
		goto errout;

	*new_cnt = pos_get_cnt(&pos);
	return 0;
errout:
	return err;
}