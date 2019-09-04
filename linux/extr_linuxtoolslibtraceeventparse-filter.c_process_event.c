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
struct filter_arg {TYPE_1__ boolean; int /*<<< orphan*/  type; } ;
struct event_format {int dummy; } ;
typedef  enum tep_errno { ____Placeholder_tep_errno } tep_errno ;

/* Variables and functions */
 int /*<<< orphan*/  FILTER_ARG_BOOLEAN ; 
 int /*<<< orphan*/  FILTER_FALSE ; 
 int TEP_ERRNO__MEM_ALLOC_FAILED ; 
 struct filter_arg* allocate_arg () ; 
 int process_filter (struct event_format*,struct filter_arg**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  tep_buffer_init (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum tep_errno
process_event(struct event_format *event, const char *filter_str,
	      struct filter_arg **parg, char *error_str)
{
	int ret;

	tep_buffer_init(filter_str, strlen(filter_str));

	ret = process_filter(event, parg, error_str, 0);
	if (ret < 0)
		return ret;

	/* If parg is NULL, then make it into FALSE */
	if (!*parg) {
		*parg = allocate_arg();
		if (*parg == NULL)
			return TEP_ERRNO__MEM_ALLOC_FAILED;

		(*parg)->type = FILTER_ARG_BOOLEAN;
		(*parg)->boolean.value = FILTER_FALSE;
	}

	return 0;
}