#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tokentype; scalar_t__ dicts; int /*<<< orphan*/  cfgname; } ;
struct TYPE_6__ {int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_ts_config ;
typedef  TYPE_2__ AlterTSConfigurationStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  DropConfigurationMapping (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTSConfigTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeConfigurationMapping (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameListToString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJECT_TSCONFIGURATION ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  TSConfigMapRelationId ; 
 int /*<<< orphan*/  TSConfigRelationId ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeConfigurationDependencies (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_ts_config_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ObjectAddress
AlterTSConfiguration(AlterTSConfigurationStmt *stmt)
{
	HeapTuple	tup;
	Oid			cfgId;
	Relation	relMap;
	ObjectAddress address;

	/* Find the configuration */
	tup = GetTSConfigTuple(stmt->cfgname);
	if (!HeapTupleIsValid(tup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("text search configuration \"%s\" does not exist",
						NameListToString(stmt->cfgname))));

	cfgId = ((Form_pg_ts_config) GETSTRUCT(tup))->oid;

	/* must be owner */
	if (!pg_ts_config_ownercheck(cfgId, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_TSCONFIGURATION,
					   NameListToString(stmt->cfgname));

	relMap = table_open(TSConfigMapRelationId, RowExclusiveLock);

	/* Add or drop mappings */
	if (stmt->dicts)
		MakeConfigurationMapping(stmt, tup, relMap);
	else if (stmt->tokentype)
		DropConfigurationMapping(stmt, tup, relMap);

	/* Update dependencies */
	makeConfigurationDependencies(tup, true, relMap);

	InvokeObjectPostAlterHook(TSConfigRelationId, cfgId, 0);

	ObjectAddressSet(address, TSConfigRelationId, cfgId);

	table_close(relMap, RowExclusiveLock);

	ReleaseSysCache(tup);

	return address;
}