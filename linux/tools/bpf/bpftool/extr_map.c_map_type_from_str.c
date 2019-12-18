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

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* map_type_name ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static int map_type_from_str(const char *type)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(map_type_name); i++)
		/* Don't allow prefixing in case of possible future shadowing */
		if (map_type_name[i] && !strcmp(map_type_name[i], type))
			return i;
	return -1;
}