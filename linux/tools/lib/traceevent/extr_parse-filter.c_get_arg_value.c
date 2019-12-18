#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tep_record {int dummy; } ;
struct TYPE_4__ {unsigned long long val; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  field; } ;
struct tep_filter_arg {int type; TYPE_2__ value; TYPE_1__ field; } ;
struct tep_event {int dummy; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int TEP_ERRNO__INVALID_ARG_TYPE ; 
 int TEP_ERRNO__NOT_A_NUMBER ; 
#define  TEP_FILTER_ARG_EXP 130 
#define  TEP_FILTER_ARG_FIELD 129 
#define  TEP_FILTER_ARG_VALUE 128 
 int /*<<< orphan*/  TEP_FILTER_NUMBER ; 
 unsigned long long get_exp_value (struct tep_event*,struct tep_filter_arg*,struct tep_record*,int*) ; 
 unsigned long long get_value (struct tep_event*,int /*<<< orphan*/ ,struct tep_record*) ; 

__attribute__((used)) static unsigned long long
get_arg_value(struct tep_event *event, struct tep_filter_arg *arg,
	      struct tep_record *record, enum tep_errno *err)
{
	switch (arg->type) {
	case TEP_FILTER_ARG_FIELD:
		return get_value(event, arg->field.field, record);

	case TEP_FILTER_ARG_VALUE:
		if (arg->value.type != TEP_FILTER_NUMBER) {
			if (!*err)
				*err = TEP_ERRNO__NOT_A_NUMBER;
		}
		return arg->value.val;

	case TEP_FILTER_ARG_EXP:
		return get_exp_value(event, arg, record, err);

	default:
		if (!*err)
			*err = TEP_ERRNO__INVALID_ARG_TYPE;
	}
	return 0;
}