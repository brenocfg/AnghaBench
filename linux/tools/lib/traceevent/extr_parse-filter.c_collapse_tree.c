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
struct TYPE_2__ {int value; } ;
struct tep_filter_arg {TYPE_1__ boolean; int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  FILTER_VAL_FALSE 130 
#define  FILTER_VAL_NORM 129 
#define  FILTER_VAL_TRUE 128 
 int TEP_ERRNO__MEM_ALLOC_FAILED ; 
 int /*<<< orphan*/  TEP_FILTER_ARG_BOOLEAN ; 
 struct tep_filter_arg* allocate_arg () ; 
 int /*<<< orphan*/  free_arg (struct tep_filter_arg*) ; 
 int /*<<< orphan*/  show_error (char*,char*) ; 
 int test_arg (struct tep_filter_arg*,struct tep_filter_arg*,char*) ; 

__attribute__((used)) static int collapse_tree(struct tep_filter_arg *arg,
			 struct tep_filter_arg **arg_collapsed, char *error_str)
{
	int ret;

	ret = test_arg(arg, arg, error_str);
	switch (ret) {
	case FILTER_VAL_NORM:
		break;

	case FILTER_VAL_TRUE:
	case FILTER_VAL_FALSE:
		free_arg(arg);
		arg = allocate_arg();
		if (arg) {
			arg->type = TEP_FILTER_ARG_BOOLEAN;
			arg->boolean.value = ret == FILTER_VAL_TRUE;
		} else {
			show_error(error_str, "Failed to allocate filter arg");
			ret = TEP_ERRNO__MEM_ALLOC_FAILED;
		}
		break;

	default:
		/* test_arg() already set the error_str */
		free_arg(arg);
		arg = NULL;
		break;
	}

	*arg_collapsed = arg;
	return ret;
}