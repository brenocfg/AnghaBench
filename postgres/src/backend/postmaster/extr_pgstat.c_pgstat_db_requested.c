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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ InvalidOid ; 
 scalar_t__ NIL ; 
 scalar_t__ list_member_oid (scalar_t__,scalar_t__) ; 
 scalar_t__ pending_write_requests ; 

__attribute__((used)) static bool
pgstat_db_requested(Oid databaseid)
{
	/*
	 * If any requests are outstanding at all, we should write the stats for
	 * shared catalogs (the "database" with OID 0).  This ensures that
	 * backends will see up-to-date stats for shared catalogs, even though
	 * they send inquiry messages mentioning only their own DB.
	 */
	if (databaseid == InvalidOid && pending_write_requests != NIL)
		return true;

	/* Search to see if there's an open request to write this database. */
	if (list_member_oid(pending_write_requests, databaseid))
		return true;

	return false;
}