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
 int ENOMEM ; 
 int /*<<< orphan*/  field_order ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_default_sort_order (struct evlist*) ; 
 scalar_t__ is_strict_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_hpp_list ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 char* setup_overhead (char*) ; 
 int setup_sort_list (int /*<<< orphan*/ *,char*,struct evlist*) ; 
 int setup_sort_order (struct evlist*) ; 
 char* sort_order ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int __setup_sorting(struct evlist *evlist)
{
	char *str;
	const char *sort_keys;
	int ret = 0;

	ret = setup_sort_order(evlist);
	if (ret)
		return ret;

	sort_keys = sort_order;
	if (sort_keys == NULL) {
		if (is_strict_order(field_order)) {
			/*
			 * If user specified field order but no sort order,
			 * we'll honor it and not add default sort orders.
			 */
			return 0;
		}

		sort_keys = get_default_sort_order(evlist);
	}

	str = strdup(sort_keys);
	if (str == NULL) {
		pr_err("Not enough memory to setup sort keys");
		return -ENOMEM;
	}

	/*
	 * Prepend overhead fields for backward compatibility.
	 */
	if (!is_strict_order(field_order)) {
		str = setup_overhead(str);
		if (str == NULL) {
			pr_err("Not enough memory to setup overhead keys");
			return -ENOMEM;
		}
	}

	ret = setup_sort_list(&perf_hpp_list, str, evlist);

	free(str);
	return ret;
}