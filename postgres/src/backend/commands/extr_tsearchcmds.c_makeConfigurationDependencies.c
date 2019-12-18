#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cfgparser; int /*<<< orphan*/  cfgowner; int /*<<< orphan*/  cfgnamespace; int /*<<< orphan*/  oid; } ;
struct TYPE_9__ {int /*<<< orphan*/  mapdict; } ;
struct TYPE_8__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  scalar_t__ Relation ;
typedef  int /*<<< orphan*/  ObjectAddresses ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_ts_config_map ;
typedef  TYPE_3__* Form_pg_ts_config ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_ts_config_map_mapcfg ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSConfigMapIndexId ; 
 int /*<<< orphan*/  TSConfigRelationId ; 
 int /*<<< orphan*/  TSDictionaryRelationId ; 
 int /*<<< orphan*/  TSParserRelationId ; 
 int /*<<< orphan*/  add_exact_object_address (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deleteDependencyRecordsFor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  deleteSharedDependencyRecordsFor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_object_addresses (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * new_object_addresses () ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_1__*,int) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_object_address_dependencies (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
makeConfigurationDependencies(HeapTuple tuple, bool removeOld,
							  Relation mapRel)
{
	Form_pg_ts_config cfg = (Form_pg_ts_config) GETSTRUCT(tuple);
	ObjectAddresses *addrs;
	ObjectAddress myself,
				referenced;

	myself.classId = TSConfigRelationId;
	myself.objectId = cfg->oid;
	myself.objectSubId = 0;

	/* for ALTER case, first flush old dependencies, except extension deps */
	if (removeOld)
	{
		deleteDependencyRecordsFor(myself.classId, myself.objectId, true);
		deleteSharedDependencyRecordsFor(myself.classId, myself.objectId, 0);
	}

	/*
	 * We use an ObjectAddresses list to remove possible duplicate
	 * dependencies from the config map info.  The pg_ts_config items
	 * shouldn't be duplicates, but might as well fold them all into one call.
	 */
	addrs = new_object_addresses();

	/* dependency on namespace */
	referenced.classId = NamespaceRelationId;
	referenced.objectId = cfg->cfgnamespace;
	referenced.objectSubId = 0;
	add_exact_object_address(&referenced, addrs);

	/* dependency on owner */
	recordDependencyOnOwner(myself.classId, myself.objectId, cfg->cfgowner);

	/* dependency on extension */
	recordDependencyOnCurrentExtension(&myself, removeOld);

	/* dependency on parser */
	referenced.classId = TSParserRelationId;
	referenced.objectId = cfg->cfgparser;
	referenced.objectSubId = 0;
	add_exact_object_address(&referenced, addrs);

	/* dependencies on dictionaries listed in config map */
	if (mapRel)
	{
		ScanKeyData skey;
		SysScanDesc scan;
		HeapTuple	maptup;

		/* CCI to ensure we can see effects of caller's changes */
		CommandCounterIncrement();

		ScanKeyInit(&skey,
					Anum_pg_ts_config_map_mapcfg,
					BTEqualStrategyNumber, F_OIDEQ,
					ObjectIdGetDatum(myself.objectId));

		scan = systable_beginscan(mapRel, TSConfigMapIndexId, true,
								  NULL, 1, &skey);

		while (HeapTupleIsValid((maptup = systable_getnext(scan))))
		{
			Form_pg_ts_config_map cfgmap = (Form_pg_ts_config_map) GETSTRUCT(maptup);

			referenced.classId = TSDictionaryRelationId;
			referenced.objectId = cfgmap->mapdict;
			referenced.objectSubId = 0;
			add_exact_object_address(&referenced, addrs);
		}

		systable_endscan(scan);
	}

	/* Record 'em (this includes duplicate elimination) */
	record_object_address_dependencies(&myself, addrs, DEPENDENCY_NORMAL);

	free_object_addresses(addrs);

	return myself;
}