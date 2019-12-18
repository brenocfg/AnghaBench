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
struct fetch_insn {unsigned int param; int /*<<< orphan*/  op; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ARG_NUM ; 
 int /*<<< orphan*/  BAD_STACK_NUM ; 
 int /*<<< orphan*/  BAD_VAR ; 
 int EINVAL ; 
 int /*<<< orphan*/  FETCH_OP_ARG ; 
 int /*<<< orphan*/  FETCH_OP_COMM ; 
 int /*<<< orphan*/  FETCH_OP_RETVAL ; 
 int /*<<< orphan*/  FETCH_OP_STACK ; 
 int /*<<< orphan*/  FETCH_OP_STACKP ; 
 unsigned long PARAM_MAX_STACK ; 
 int /*<<< orphan*/  RETVAL_ON_PROBE ; 
 unsigned int TPARG_FL_FENTRY ; 
 unsigned int TPARG_FL_KERNEL ; 
 unsigned int TPARG_FL_MASK ; 
 unsigned int TPARG_FL_RETURN ; 
 scalar_t__ isdigit (char) ; 
 int kstrtoul (char*,int,unsigned long*) ; 
 int str_has_prefix (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  trace_probe_log_err (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_probe_vars(char *arg, const struct fetch_type *t,
			struct fetch_insn *code, unsigned int flags, int offs)
{
	unsigned long param;
	int ret = 0;
	int len;

	if (strcmp(arg, "retval") == 0) {
		if (flags & TPARG_FL_RETURN) {
			code->op = FETCH_OP_RETVAL;
		} else {
			trace_probe_log_err(offs, RETVAL_ON_PROBE);
			ret = -EINVAL;
		}
	} else if ((len = str_has_prefix(arg, "stack"))) {
		if (arg[len] == '\0') {
			code->op = FETCH_OP_STACKP;
		} else if (isdigit(arg[len])) {
			ret = kstrtoul(arg + len, 10, &param);
			if (ret) {
				goto inval_var;
			} else if ((flags & TPARG_FL_KERNEL) &&
				    param > PARAM_MAX_STACK) {
				trace_probe_log_err(offs, BAD_STACK_NUM);
				ret = -EINVAL;
			} else {
				code->op = FETCH_OP_STACK;
				code->param = (unsigned int)param;
			}
		} else
			goto inval_var;
	} else if (strcmp(arg, "comm") == 0) {
		code->op = FETCH_OP_COMM;
#ifdef CONFIG_HAVE_FUNCTION_ARG_ACCESS_API
	} else if (((flags & TPARG_FL_MASK) ==
		    (TPARG_FL_KERNEL | TPARG_FL_FENTRY)) &&
		   (len = str_has_prefix(arg, "arg"))) {
		ret = kstrtoul(arg + len, 10, &param);
		if (ret) {
			goto inval_var;
		} else if (!param || param > PARAM_MAX_STACK) {
			trace_probe_log_err(offs, BAD_ARG_NUM);
			return -EINVAL;
		}
		code->op = FETCH_OP_ARG;
		code->param = (unsigned int)param - 1;
#endif
	} else
		goto inval_var;

	return ret;

inval_var:
	trace_probe_log_err(offs, BAD_VAR);
	return -EINVAL;
}