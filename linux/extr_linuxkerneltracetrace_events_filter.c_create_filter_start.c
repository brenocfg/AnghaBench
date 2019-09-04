#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct filter_parse_error {int dummy; } ;
struct event_filter {int /*<<< orphan*/  filter_string; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __free_filter (struct event_filter*) ; 
 int /*<<< orphan*/  kfree (struct filter_parse_error*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_filter_start(char *filter_string, bool set_str,
			       struct filter_parse_error **pse,
			       struct event_filter **filterp)
{
	struct event_filter *filter;
	struct filter_parse_error *pe = NULL;
	int err = 0;

	if (WARN_ON_ONCE(*pse || *filterp))
		return -EINVAL;

	filter = kzalloc(sizeof(*filter), GFP_KERNEL);
	if (filter && set_str) {
		filter->filter_string = kstrdup(filter_string, GFP_KERNEL);
		if (!filter->filter_string)
			err = -ENOMEM;
	}

	pe = kzalloc(sizeof(*pe), GFP_KERNEL);

	if (!filter || !pe || err) {
		kfree(pe);
		__free_filter(filter);
		return -ENOMEM;
	}

	/* we're committed to creating a new filter */
	*filterp = filter;
	*pse = pe;

	return 0;
}