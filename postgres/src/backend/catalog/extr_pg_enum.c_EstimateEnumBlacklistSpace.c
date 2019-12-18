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
typedef  int Size ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ enum_blacklist ; 
 size_t hash_get_num_entries (scalar_t__) ; 

Size
EstimateEnumBlacklistSpace(void)
{
	size_t		entries;

	if (enum_blacklist)
		entries = hash_get_num_entries(enum_blacklist);
	else
		entries = 0;

	/* Add one for the terminator. */
	return sizeof(Oid) * (entries + 1);
}