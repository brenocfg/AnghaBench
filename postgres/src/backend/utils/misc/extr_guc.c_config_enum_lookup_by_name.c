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
struct config_enum_entry {int val; scalar_t__ name; } ;
struct config_enum {struct config_enum_entry* options; } ;

/* Variables and functions */
 scalar_t__ pg_strcasecmp (char const*,scalar_t__) ; 

bool
config_enum_lookup_by_name(struct config_enum *record, const char *value,
						   int *retval)
{
	const struct config_enum_entry *entry;

	for (entry = record->options; entry && entry->name; entry++)
	{
		if (pg_strcasecmp(value, entry->name) == 0)
		{
			*retval = entry->val;
			return true;
		}
	}

	*retval = 0;
	return false;
}