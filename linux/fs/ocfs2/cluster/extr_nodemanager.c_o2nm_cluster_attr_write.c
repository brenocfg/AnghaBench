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
typedef  unsigned long u32 ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 unsigned long simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t o2nm_cluster_attr_write(const char *page, ssize_t count,
                                       unsigned int *val)
{
	unsigned long tmp;
	char *p = (char *)page;

	tmp = simple_strtoul(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		return -EINVAL;

	if (tmp == 0)
		return -EINVAL;
	if (tmp >= (u32)-1)
		return -ERANGE;

	*val = tmp;

	return count;
}