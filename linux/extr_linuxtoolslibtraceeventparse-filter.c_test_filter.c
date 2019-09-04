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
struct filter_arg {int type; TYPE_1__ boolean; } ;
struct event_format {int dummy; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
#define  FILTER_ARG_BOOLEAN 134 
#define  FILTER_ARG_EXP 133 
#define  FILTER_ARG_FIELD 132 
#define  FILTER_ARG_NUM 131 
#define  FILTER_ARG_OP 130 
#define  FILTER_ARG_STR 129 
#define  FILTER_ARG_VALUE 128 
 int TEP_ERRNO__INVALID_ARG_TYPE ; 
 int /*<<< orphan*/  get_arg_value (struct event_format*,struct filter_arg*,struct tep_record*,int*) ; 
 int test_num (struct event_format*,struct filter_arg*,struct tep_record*,int*) ; 
 int test_op (struct event_format*,struct filter_arg*,struct tep_record*,int*) ; 
 int test_str (struct event_format*,struct filter_arg*,struct tep_record*,int*) ; 

__attribute__((used)) static int test_filter(struct event_format *event, struct filter_arg *arg,
		       struct tep_record *record, enum tep_errno *err)
{
	if (*err) {
		/*
		 * There was an error, no need to process anymore.
		 */
		return 0;
	}

	switch (arg->type) {
	case FILTER_ARG_BOOLEAN:
		/* easy case */
		return arg->boolean.value;

	case FILTER_ARG_OP:
		return test_op(event, arg, record, err);

	case FILTER_ARG_NUM:
		return test_num(event, arg, record, err);

	case FILTER_ARG_STR:
		return test_str(event, arg, record, err);

	case FILTER_ARG_EXP:
	case FILTER_ARG_VALUE:
	case FILTER_ARG_FIELD:
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