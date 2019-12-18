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
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  ApplySetting (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DbRoleSettingRelationId ; 
 int /*<<< orphan*/  GetCatalogSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsUnderPostmaster ; 
 int /*<<< orphan*/  PGC_S_DATABASE ; 
 int /*<<< orphan*/  PGC_S_DATABASE_USER ; 
 int /*<<< orphan*/  PGC_S_GLOBAL ; 
 int /*<<< orphan*/  PGC_S_USER ; 
 int /*<<< orphan*/  RegisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnregisterSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_settings(Oid databaseid, Oid roleid)
{
	Relation	relsetting;
	Snapshot	snapshot;

	if (!IsUnderPostmaster)
		return;

	relsetting = table_open(DbRoleSettingRelationId, AccessShareLock);

	/* read all the settings under the same snapshot for efficiency */
	snapshot = RegisterSnapshot(GetCatalogSnapshot(DbRoleSettingRelationId));

	/* Later settings are ignored if set earlier. */
	ApplySetting(snapshot, databaseid, roleid, relsetting, PGC_S_DATABASE_USER);
	ApplySetting(snapshot, InvalidOid, roleid, relsetting, PGC_S_USER);
	ApplySetting(snapshot, databaseid, InvalidOid, relsetting, PGC_S_DATABASE);
	ApplySetting(snapshot, InvalidOid, InvalidOid, relsetting, PGC_S_GLOBAL);

	UnregisterSnapshot(snapshot);
	table_close(relsetting, AccessShareLock);
}