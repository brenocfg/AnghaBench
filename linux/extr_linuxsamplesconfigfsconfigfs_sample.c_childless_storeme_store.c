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
struct config_item {int dummy; } ;
struct childless {unsigned long storeme; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ERANGE ; 
 unsigned long INT_MAX ; 
 unsigned long simple_strtoul (char*,char**,int) ; 
 struct childless* to_childless (struct config_item*) ; 

__attribute__((used)) static ssize_t childless_storeme_store(struct config_item *item,
		const char *page, size_t count)
{
	struct childless *childless = to_childless(item);
	unsigned long tmp;
	char *p = (char *) page;

	tmp = simple_strtoul(p, &p, 10);
	if (!p || (*p && (*p != '\n')))
		return -EINVAL;

	if (tmp > INT_MAX)
		return -ERANGE;

	childless->storeme = tmp;

	return count;
}