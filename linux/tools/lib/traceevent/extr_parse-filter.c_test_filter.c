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
struct TYPE_2__ {int value; } ;
struct tep_filter_arg {int type; TYPE_1__ boolean; } ;
struct tep_event {int dummy; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int TEP_ERRNO__INVALID_ARG_TYPE ; 
#define  TEP_FILTER_ARG_BOOLEAN 134 
#define  TEP_FILTER_ARG_EXP 133 
#define  TEP_FILTER_ARG_FIELD 132 
#define  TEP_FILTER_ARG_NUM 131 
#define  TEP_FILTER_ARG_OP 130 
#define  TEP_FILTER_ARG_STR 129 
#define  TEP_FILTER_ARG_VALUE 128 
 int /*<<< orphan*/  get_arg_value (struct tep_event*,struct tep_filter_arg*,struct tep_record*,int*) ; 
 int test_num (struct tep_event*,struct tep_filter_arg*,struct tep_record*,int*) ; 
 int test_op (struct tep_event*,struct tep_filter_arg*,struct tep_record*,int*) ; 
 int test_str (struct tep_event*,struct tep_filter_arg*,struct tep_record*,int*) ; 

__attribute__((used)) static int test_filter(struct tep_event *event, struct tep_filter_arg *arg,
		       struct tep_record *record, enum tep_errno *err)
{
	if (*err) {
		/*
		 * There was an error, no need to process anymore.
		 */
		return 0;
	}

	switch (arg->type) {
	case TEP_FILTER_ARG_BOOLEAN:
		/* easy case */
		return arg->boolean.value;

	case TEP_FILTER_ARG_OP:
		return test_op(event, arg, record, err);

	case TEP_FILTER_ARG_NUM:
		return test_num(event, arg, record, err);

	case TEP_FILTER_ARG_STR:
		return test_str(event, arg, record, err);

	case TEP_FILTER_ARG_EXP:
	case TEP_FILTER_ARG_VALUE:
	case TEP_FILTER_ARG_FIELD:
		/*
		 * Expressions, fields and values evaluate
		 * to true if they return non zero
		 */
		return !!get_arg_value(event, arg, record, err);

	default:
		if (!*err)
			*err = TEP_ERRNO__INVALID_ARG_TYPE;
		return 0;
	}
}