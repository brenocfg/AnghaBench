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
struct fetch_type {int dummy; } ;
struct fetch_insn {int op; unsigned int param; unsigned long immediate; char* data; long offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_DEREF_OFFS ; 
 int /*<<< orphan*/  BAD_FETCH_ARG ; 
 int /*<<< orphan*/  BAD_FILE_OFFS ; 
 int /*<<< orphan*/  BAD_IMM ; 
 int /*<<< orphan*/  BAD_MEM_ADDR ; 
 int /*<<< orphan*/  BAD_REG_NAME ; 
 int /*<<< orphan*/  COMM_CANT_DEREF ; 
 int /*<<< orphan*/  DEREF_NEED_BRACE ; 
 int /*<<< orphan*/  DEREF_OPEN_BRACE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int FETCH_NOP_SYMBOL ; 
 int FETCH_OP_COMM ; 
 int FETCH_OP_DATA ; 
 void* FETCH_OP_DEREF ; 
 int FETCH_OP_FOFFS ; 
 void* FETCH_OP_IMM ; 
 scalar_t__ FETCH_OP_NOP ; 
 int FETCH_OP_REG ; 
 int FETCH_OP_UDEREF ; 
 int /*<<< orphan*/  FILE_ON_KPROBE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SYM_ON_UPROBE ; 
 int /*<<< orphan*/  TOO_MANY_OPS ; 
 unsigned int TPARG_FL_KERNEL ; 
 int __parse_imm_string (char*,char**,int) ; 
 struct fetch_type* find_fetch_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int kstrtol (char*,int /*<<< orphan*/ ,long*) ; 
 int kstrtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 int parse_probe_vars (char*,struct fetch_type const*,struct fetch_insn*,unsigned int,int) ; 
 int regs_query_register_offset (char*) ; 
 int str_to_immediate (char*,unsigned long*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  trace_probe_log_err (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse_probe_arg(char *arg, const struct fetch_type *type,
		struct fetch_insn **pcode, struct fetch_insn *end,
		unsigned int flags, int offs)
{
	struct fetch_insn *code = *pcode;
	unsigned long param;
	int deref = FETCH_OP_DEREF;
	long offset = 0;
	char *tmp;
	int ret = 0;

	switch (arg[0]) {
	case '$':
		ret = parse_probe_vars(arg + 1, type, code, flags, offs);
		break;

	case '%':	/* named register */
		ret = regs_query_register_offset(arg + 1);
		if (ret >= 0) {
			code->op = FETCH_OP_REG;
			code->param = (unsigned int)ret;
			ret = 0;
		} else
			trace_probe_log_err(offs, BAD_REG_NAME);
		break;

	case '@':	/* memory, file-offset or symbol */
		if (isdigit(arg[1])) {
			ret = kstrtoul(arg + 1, 0, &param);
			if (ret) {
				trace_probe_log_err(offs, BAD_MEM_ADDR);
				break;
			}
			/* load address */
			code->op = FETCH_OP_IMM;
			code->immediate = param;
		} else if (arg[1] == '+') {
			/* kprobes don't support file offsets */
			if (flags & TPARG_FL_KERNEL) {
				trace_probe_log_err(offs, FILE_ON_KPROBE);
				return -EINVAL;
			}
			ret = kstrtol(arg + 2, 0, &offset);
			if (ret) {
				trace_probe_log_err(offs, BAD_FILE_OFFS);
				break;
			}

			code->op = FETCH_OP_FOFFS;
			code->immediate = (unsigned long)offset;  // imm64?
		} else {
			/* uprobes don't support symbols */
			if (!(flags & TPARG_FL_KERNEL)) {
				trace_probe_log_err(offs, SYM_ON_UPROBE);
				return -EINVAL;
			}
			/* Preserve symbol for updating */
			code->op = FETCH_NOP_SYMBOL;
			code->data = kstrdup(arg + 1, GFP_KERNEL);
			if (!code->data)
				return -ENOMEM;
			if (++code == end) {
				trace_probe_log_err(offs, TOO_MANY_OPS);
				return -EINVAL;
			}
			code->op = FETCH_OP_IMM;
			code->immediate = 0;
		}
		/* These are fetching from memory */
		if (++code == end) {
			trace_probe_log_err(offs, TOO_MANY_OPS);
			return -EINVAL;
		}
		*pcode = code;
		code->op = FETCH_OP_DEREF;
		code->offset = offset;
		break;

	case '+':	/* deref memory */
	case '-':
		if (arg[1] == 'u') {
			deref = FETCH_OP_UDEREF;
			arg[1] = arg[0];
			arg++;
		}
		if (arg[0] == '+')
			arg++;	/* Skip '+', because kstrtol() rejects it. */
		tmp = strchr(arg, '(');
		if (!tmp) {
			trace_probe_log_err(offs, DEREF_NEED_BRACE);
			return -EINVAL;
		}
		*tmp = '\0';
		ret = kstrtol(arg, 0, &offset);
		if (ret) {
			trace_probe_log_err(offs, BAD_DEREF_OFFS);
			break;
		}
		offs += (tmp + 1 - arg) + (arg[0] != '-' ? 1 : 0);
		arg = tmp + 1;
		tmp = strrchr(arg, ')');
		if (!tmp) {
			trace_probe_log_err(offs + strlen(arg),
					    DEREF_OPEN_BRACE);
			return -EINVAL;
		} else {
			const struct fetch_type *t2 = find_fetch_type(NULL);

			*tmp = '\0';
			ret = parse_probe_arg(arg, t2, &code, end, flags, offs);
			if (ret)
				break;
			if (code->op == FETCH_OP_COMM ||
			    code->op == FETCH_OP_DATA) {
				trace_probe_log_err(offs, COMM_CANT_DEREF);
				return -EINVAL;
			}
			if (++code == end) {
				trace_probe_log_err(offs, TOO_MANY_OPS);
				return -EINVAL;
			}
			*pcode = code;

			code->op = deref;
			code->offset = offset;
		}
		break;
	case '\\':	/* Immediate value */
		if (arg[1] == '"') {	/* Immediate string */
			ret = __parse_imm_string(arg + 2, &tmp, offs + 2);
			if (ret)
				break;
			code->op = FETCH_OP_DATA;
			code->data = tmp;
		} else {
			ret = str_to_immediate(arg + 1, &code->immediate);
			if (ret)
				trace_probe_log_err(offs + 1, BAD_IMM);
			else
				code->op = FETCH_OP_IMM;
		}
		break;
	}
	if (!ret && code->op == FETCH_OP_NOP) {
		/* Parsed, but do not find fetch method */
		trace_probe_log_err(offs, BAD_FETCH_ARG);
		ret = -EINVAL;
	}
	return ret;
}