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
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct tep_filter_arg {int type; TYPE_1__ boolean; } ;
struct tep_event_filter {int dummy; } ;

/* Variables and functions */
#define  TEP_FILTER_ARG_BOOLEAN 134 
#define  TEP_FILTER_ARG_EXP 133 
#define  TEP_FILTER_ARG_FIELD 132 
#define  TEP_FILTER_ARG_NUM 131 
#define  TEP_FILTER_ARG_OP 130 
#define  TEP_FILTER_ARG_STR 129 
#define  TEP_FILTER_ARG_VALUE 128 
 int /*<<< orphan*/  asprintf (char**,char*) ; 
 char* exp_to_str (struct tep_event_filter*,struct tep_filter_arg*) ; 
 char* field_to_str (struct tep_event_filter*,struct tep_filter_arg*) ; 
 char* num_to_str (struct tep_event_filter*,struct tep_filter_arg*) ; 
 char* op_to_str (struct tep_event_filter*,struct tep_filter_arg*) ; 
 char* str_to_str (struct tep_event_filter*,struct tep_filter_arg*) ; 
 char* val_to_str (struct tep_event_filter*,struct tep_filter_arg*) ; 

__attribute__((used)) static char *arg_to_str(struct tep_event_filter *filter, struct tep_filter_arg *arg)
{
	char *str = NULL;

	switch (arg->type) {
	case TEP_FILTER_ARG_BOOLEAN:
		asprintf(&str, arg->boolean.value ? "TRUE" : "FALSE");
		return str;

	case TEP_FILTER_ARG_OP:
		return op_to_str(filter, arg);

	case TEP_FILTER_ARG_NUM:
		return num_to_str(filter, arg);

	case TEP_FILTER_ARG_STR:
		return str_to_str(filter, arg);

	case TEP_FILTER_ARG_VALUE:
		return val_to_str(filter, arg);

	case TEP_FILTER_ARG_FIELD:
		return field_to_str(filter, arg);

	case TEP_FILTER_ARG_EXP:
		return exp_to_str(filter, arg);

	default:
		/* ?? */
		return NULL;
	}

}