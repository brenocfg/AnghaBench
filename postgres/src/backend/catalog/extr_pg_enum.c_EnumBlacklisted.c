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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/ * enum_blacklist ; 
 int /*<<< orphan*/  hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

bool
EnumBlacklisted(Oid enum_id)
{
	bool		found;

	/* If we've made no blacklist table, all values are safe */
	if (enum_blacklist == NULL)
		return false;

	/* Else, is it in the table? */
	(void) hash_search(enum_blacklist, &enum_id, HASH_FIND, &found);
	return found;
}