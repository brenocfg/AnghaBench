#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tep_record {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
struct tep_filter_arg {TYPE_1__ exp; } ;
struct tep_event {int dummy; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int TEP_ERRNO__INVALID_EXP_TYPE ; 
#define  TEP_FILTER_EXP_ADD 138 
#define  TEP_FILTER_EXP_AND 137 
#define  TEP_FILTER_EXP_DIV 136 
#define  TEP_FILTER_EXP_LSHIFT 135 
#define  TEP_FILTER_EXP_MOD 134 
#define  TEP_FILTER_EXP_MUL 133 
#define  TEP_FILTER_EXP_NOT 132 
#define  TEP_FILTER_EXP_OR 131 
#define  TEP_FILTER_EXP_RSHIFT 130 
#define  TEP_FILTER_EXP_SUB 129 
#define  TEP_FILTER_EXP_XOR 128 
 unsigned long long get_arg_value (struct tep_event*,int /*<<< orphan*/ ,struct tep_record*,int*) ; 

__attribute__((used)) static unsigned long long
get_exp_value(struct tep_event *event, struct tep_filter_arg *arg,
	      struct tep_record *record, enum tep_errno *err)
{
	unsigned long long lval, rval;

	lval = get_arg_value(event, arg->exp.left, record, err);
	rval = get_arg_value(event, arg->exp.right, record, err);

	if (*err) {
		/*
		 * There was an error, no need to process anymore.
		 */
		return 0;
	}

	switch (arg->exp.type) {
	case TEP_FILTER_EXP_ADD:
		return lval + rval;

	case TEP_FILTER_EXP_SUB:
		return lval - rval;

	case TEP_FILTER_EXP_MUL:
		return lval * rval;

	case TEP_FILTER_EXP_DIV:
		return lval / rval;

	case TEP_FILTER_EXP_MOD:
		return lval % rval;

	case TEP_FILTER_EXP_RSHIFT:
		return lval >> rval;

	case TEP_FILTER_EXP_LSHIFT:
		return lval << rval;

	case TEP_FILTER_EXP_AND:
		return lval & rval;

	case TEP_FILTER_EXP_OR:
		return lval | rval;

	case TEP_FILTER_EXP_XOR:
		return lval ^ rval;

	case TEP_FILTER_EXP_NOT:
	default:
		if (!*err)
			*err = TEP_ERRNO__INVALID_EXP_TYPE;
	}
	return 0;
}