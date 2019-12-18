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
typedef  enum rfkill_type { ____Placeholder_rfkill_type } rfkill_type ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int NUM_RFKILL_TYPES ; 
 int RFKILL_TYPE_ALL ; 
 int /*<<< orphan*/ * rfkill_types ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

enum rfkill_type rfkill_find_type(const char *name)
{
	int i;

	BUILD_BUG_ON(ARRAY_SIZE(rfkill_types) != NUM_RFKILL_TYPES);

	if (!name)
		return RFKILL_TYPE_ALL;

	for (i = 1; i < NUM_RFKILL_TYPES; i++)
		if (!strcmp(name, rfkill_types[i]))
			return i;
	return RFKILL_TYPE_ALL;
}