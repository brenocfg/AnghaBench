#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct tep_filter_arg* left; } ;
struct TYPE_6__ {struct tep_filter_arg* left; } ;
struct TYPE_5__ {struct tep_filter_arg* left; } ;
struct tep_filter_arg {int type; TYPE_1__ num; TYPE_3__ op; TYPE_2__ exp; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int TEP_ERRNO__INVALID_ARG_TYPE ; 
 int const TEP_FILTER_ARG_BOOLEAN ; 
#define  TEP_FILTER_ARG_EXP 130 
 int const TEP_FILTER_ARG_FIELD ; 
#define  TEP_FILTER_ARG_NUM 129 
#define  TEP_FILTER_ARG_OP 128 
 struct tep_filter_arg* rotate_op_right (struct tep_filter_arg*,struct tep_filter_arg*) ; 

__attribute__((used)) static enum tep_errno add_left(struct tep_filter_arg *op, struct tep_filter_arg *arg)
{
	switch (op->type) {
	case TEP_FILTER_ARG_EXP:
		if (arg->type == TEP_FILTER_ARG_OP)
			arg = rotate_op_right(arg, op);
		op->exp.left = arg;
		break;

	case TEP_FILTER_ARG_OP:
		op->op.left = arg;
		break;
	case TEP_FILTER_ARG_NUM:
		if (arg->type == TEP_FILTER_ARG_OP)
			arg = rotate_op_right(arg, op);

		/* left arg of compares must be a field */
		if (arg->type != TEP_FILTER_ARG_FIELD &&
		    arg->type != TEP_FILTER_ARG_BOOLEAN)
			return TEP_ERRNO__INVALID_ARG_TYPE;
		op->num.left = arg;
		break;
	default:
		return TEP_ERRNO__INVALID_ARG_TYPE;
	}
	return 0;
}