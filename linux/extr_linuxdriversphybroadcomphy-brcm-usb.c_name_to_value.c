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
struct value_to_name_map {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int name_to_value(struct value_to_name_map *table, int count,
			 const char *name, int *value)
{
	int x;

	*value = 0;
	for (x = 0; x < count; x++) {
		if (sysfs_streq(name, table[x].name)) {
			*value = x;
			return 0;
		}
	}
	return -EINVAL;
}