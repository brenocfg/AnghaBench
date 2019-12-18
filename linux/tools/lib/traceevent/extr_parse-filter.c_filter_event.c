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
struct tep_filter_type {struct tep_filter_arg* filter; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
struct tep_filter_arg {TYPE_1__ boolean; int /*<<< orphan*/  type; } ;
struct tep_event_filter {int dummy; } ;
struct tep_event {int /*<<< orphan*/  id; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int TEP_ERRNO__MEM_ALLOC_FAILED ; 
 int /*<<< orphan*/  TEP_FILTER_ARG_BOOLEAN ; 
 int /*<<< orphan*/  TEP_FILTER_TRUE ; 
 struct tep_filter_type* add_filter_type (struct tep_event_filter*,int /*<<< orphan*/ ) ; 
 struct tep_filter_arg* allocate_arg () ; 
 int /*<<< orphan*/  free_arg (struct tep_filter_arg*) ; 
 int process_event (struct tep_event*,char const*,struct tep_filter_arg**,char*) ; 

__attribute__((used)) static enum tep_errno
filter_event(struct tep_event_filter *filter, struct tep_event *event,
	     const char *filter_str, char *error_str)
{
	struct tep_filter_type *filter_type;
	struct tep_filter_arg *arg;
	enum tep_errno ret;

	if (filter_str) {
		ret = process_event(event, filter_str, &arg, error_str);
		if (ret < 0)
			return ret;

	} else {
		/* just add a TRUE arg */
		arg = allocate_arg();
		if (arg == NULL)
			return TEP_ERRNO__MEM_ALLOC_FAILED;

		arg->type = TEP_FILTER_ARG_BOOLEAN;
		arg->boolean.value = TEP_FILTER_TRUE;
	}

	filter_type = add_filter_type(filter, event->id);
	if (filter_type == NULL)
		return TEP_ERRNO__MEM_ALLOC_FAILED;

	if (filter_type->filter)
		free_arg(filter_type->filter);
	filter_type->filter = arg;

	return 0;
}