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
struct tep_filter_arg {TYPE_1__ num; } ;
struct tep_event {int dummy; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int TEP_ERRNO__ILLEGAL_INTEGER_CMP ; 
#define  TEP_FILTER_CMP_EQ 133 
#define  TEP_FILTER_CMP_GE 132 
#define  TEP_FILTER_CMP_GT 131 
#define  TEP_FILTER_CMP_LE 130 
#define  TEP_FILTER_CMP_LT 129 
#define  TEP_FILTER_CMP_NE 128 
 unsigned long long get_arg_value (struct tep_event*,int /*<<< orphan*/ ,struct tep_record*,int*) ; 

__attribute__((used)) static int test_num(struct tep_event *event, struct tep_filter_arg *arg,
		    struct tep_record *record, enum tep_errno *err)
{
	unsigned long long lval, rval;

	lval = get_arg_value(event, arg->num.left, record, err);
	rval = get_arg_value(event, arg->num.right, record, err);

	if (*err) {
		/*
		 * There was an error, no need to process anymore.
		 */
		return 0;
	}

	switch (arg->num.type) {
	case TEP_FILTER_CMP_EQ:
		return lval == rval;

	case TEP_FILTER_CMP_NE:
		return lval != rval;

	case TEP_FILTER_CMP_GT:
		return lval > rval;

	case TEP_FILTER_CMP_LT:
		return lval < rval;

	case TEP_FILTER_CMP_GE:
		return lval >= rval;

	case TEP_FILTER_CMP_LE:
		return lval <= rval;

	default:
		if (!*err)
			*err = TEP_ERRNO__ILLEGAL_INTEGER_CMP;
		return 0;
	}
}