#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct tep_filter_arg* left; int /*<<< orphan*/  type; struct tep_filter_arg* right; } ;
struct TYPE_7__ {struct tep_filter_arg* right; struct tep_filter_arg* left; } ;
struct TYPE_6__ {struct tep_filter_arg* right; struct tep_filter_arg* left; } ;
struct TYPE_5__ {int value; } ;
struct tep_filter_arg {int type; TYPE_4__ op; TYPE_3__ num; TYPE_2__ exp; TYPE_1__ boolean; } ;

/* Variables and functions */
#define  FILTER_VAL_FALSE 137 
#define  FILTER_VAL_NORM 136 
#define  FILTER_VAL_TRUE 135 
 int TEP_ERRNO__BAD_FILTER_ARG ; 
#define  TEP_FILTER_ARG_BOOLEAN 134 
#define  TEP_FILTER_ARG_EXP 133 
#define  TEP_FILTER_ARG_FIELD 132 
#define  TEP_FILTER_ARG_NUM 131 
#define  TEP_FILTER_ARG_OP 130 
#define  TEP_FILTER_ARG_STR 129 
#define  TEP_FILTER_ARG_VALUE 128 
 int /*<<< orphan*/  TEP_FILTER_OP_AND ; 
 int /*<<< orphan*/  TEP_FILTER_OP_NOT ; 
 int /*<<< orphan*/  TEP_FILTER_OP_OR ; 
 int reparent_op_arg (struct tep_filter_arg*,struct tep_filter_arg*,struct tep_filter_arg*,char*) ; 
 int /*<<< orphan*/  show_error (char*,char*) ; 

__attribute__((used)) static int test_arg(struct tep_filter_arg *parent, struct tep_filter_arg *arg,
		    char *error_str)
{
	int lval, rval;

	switch (arg->type) {

		/* bad case */
	case TEP_FILTER_ARG_BOOLEAN:
		return FILTER_VAL_FALSE + arg->boolean.value;

		/* good cases: */
	case TEP_FILTER_ARG_STR:
	case TEP_FILTER_ARG_VALUE:
	case TEP_FILTER_ARG_FIELD:
		return FILTER_VAL_NORM;

	case TEP_FILTER_ARG_EXP:
		lval = test_arg(arg, arg->exp.left, error_str);
		if (lval != FILTER_VAL_NORM)
			return lval;
		rval = test_arg(arg, arg->exp.right, error_str);
		if (rval != FILTER_VAL_NORM)
			return rval;
		return FILTER_VAL_NORM;

	case TEP_FILTER_ARG_NUM:
		lval = test_arg(arg, arg->num.left, error_str);
		if (lval != FILTER_VAL_NORM)
			return lval;
		rval = test_arg(arg, arg->num.right, error_str);
		if (rval != FILTER_VAL_NORM)
			return rval;
		return FILTER_VAL_NORM;

	case TEP_FILTER_ARG_OP:
		if (arg->op.type != TEP_FILTER_OP_NOT) {
			lval = test_arg(arg, arg->op.left, error_str);
			switch (lval) {
			case FILTER_VAL_NORM:
				break;
			case FILTER_VAL_TRUE:
				if (arg->op.type == TEP_FILTER_OP_OR)
					return FILTER_VAL_TRUE;
				rval = test_arg(arg, arg->op.right, error_str);
				if (rval != FILTER_VAL_NORM)
					return rval;

				return reparent_op_arg(parent, arg, arg->op.right,
						       error_str);

			case FILTER_VAL_FALSE:
				if (arg->op.type == TEP_FILTER_OP_AND)
					return FILTER_VAL_FALSE;
				rval = test_arg(arg, arg->op.right, error_str);
				if (rval != FILTER_VAL_NORM)
					return rval;

				return reparent_op_arg(parent, arg, arg->op.right,
						       error_str);

			default:
				return lval;
			}
		}

		rval = test_arg(arg, arg->op.right, error_str);
		switch (rval) {
		case FILTER_VAL_NORM:
		default:
			break;

		case FILTER_VAL_TRUE:
			if (arg->op.type == TEP_FILTER_OP_OR)
				return FILTER_VAL_TRUE;
			if (arg->op.type == TEP_FILTER_OP_NOT)
				return FILTER_VAL_FALSE;

			return reparent_op_arg(parent, arg, arg->op.left,
					       error_str);

		case FILTER_VAL_FALSE:
			if (arg->op.type == TEP_FILTER_OP_AND)
				return FILTER_VAL_FALSE;
			if (arg->op.type == TEP_FILTER_OP_NOT)
				return FILTER_VAL_TRUE;

			return reparent_op_arg(parent, arg, arg->op.left,
					       error_str);
		}

		return rval;
	default:
		show_error(error_str, "bad arg in filter tree");
		return TEP_ERRNO__BAD_FILTER_ARG;
	}
	return FILTER_VAL_NORM;
}