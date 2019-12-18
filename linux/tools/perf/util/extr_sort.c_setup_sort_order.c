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
struct evlist {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_default_sort_order (struct evlist*) ; 
 scalar_t__ is_strict_order (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 char* sort_order ; 

__attribute__((used)) static int setup_sort_order(struct evlist *evlist)
{
	char *new_sort_order;

	/*
	 * Append '+'-prefixed sort order to the default sort
	 * order string.
	 */
	if (!sort_order || is_strict_order(sort_order))
		return 0;

	if (sort_order[1] == '\0') {
		pr_err("Invalid --sort key: `+'");
		return -EINVAL;
	}

	/*
	 * We allocate new sort_order string, but we never free it,
	 * because it's checked over the rest of the code.
	 */
	if (asprintf(&new_sort_order, "%s,%s",
		     get_default_sort_order(evlist), sort_order + 1) < 0) {
		pr_err("Not enough memory to set up --sort");
		return -ENOMEM;
	}

	sort_order = new_sort_order;
	return 0;
}