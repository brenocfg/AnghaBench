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
struct constant_table {int value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int __lookup_constant(const struct constant_table *tbl, size_t tbl_size,
		      const char *name, int not_found)
{
	unsigned int i;

	for (i = 0; i < tbl_size; i++)
		if (strcmp(name, tbl[i].name) == 0)
			return tbl[i].value;

	return not_found;
}