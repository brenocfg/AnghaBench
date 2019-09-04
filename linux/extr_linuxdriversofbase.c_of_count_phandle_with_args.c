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
struct of_phandle_iterator {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int of_phandle_iterator_init (struct of_phandle_iterator*,struct device_node const*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int of_phandle_iterator_next (struct of_phandle_iterator*) ; 

int of_count_phandle_with_args(const struct device_node *np, const char *list_name,
				const char *cells_name)
{
	struct of_phandle_iterator it;
	int rc, cur_index = 0;

	rc = of_phandle_iterator_init(&it, np, list_name, cells_name, 0);
	if (rc)
		return rc;

	while ((rc = of_phandle_iterator_next(&it)) == 0)
		cur_index += 1;

	if (rc != -ENOENT)
		return rc;

	return cur_index;
}