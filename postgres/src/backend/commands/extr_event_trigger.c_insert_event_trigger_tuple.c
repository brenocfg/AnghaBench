#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_11__ {scalar_t__ objectSubId; void* objectId; int /*<<< orphan*/  classId; } ;
struct TYPE_10__ {int /*<<< orphan*/  rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  int /*<<< orphan*/  NameData ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_event_trigger_evtenabled ; 
 int Anum_pg_event_trigger_evtevent ; 
 int Anum_pg_event_trigger_evtfoid ; 
 int Anum_pg_event_trigger_evtname ; 
 int Anum_pg_event_trigger_evtowner ; 
 int Anum_pg_event_trigger_evttags ; 
 int Anum_pg_event_trigger_oid ; 
 int /*<<< orphan*/  CatalogTupleInsert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  EventTriggerOidIndexId ; 
 int /*<<< orphan*/  EventTriggerRelationId ; 
 void* GetNewOidWithIndex (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InvokeObjectPostCreateHook (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int Natts_pg_trigger ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 int /*<<< orphan*/  ProcedureRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  TRIGGER_FIRES_ON_ORIGIN ; 
 int /*<<< orphan*/  filter_list_to_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOnCurrentExtension (TYPE_2__*,int) ; 
 int /*<<< orphan*/  recordDependencyOnOwner (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
insert_event_trigger_tuple(const char *trigname, const char *eventname, Oid evtOwner,
						   Oid funcoid, List *taglist)
{
	Relation	tgrel;
	Oid			trigoid;
	HeapTuple	tuple;
	Datum		values[Natts_pg_trigger];
	bool		nulls[Natts_pg_trigger];
	NameData	evtnamedata,
				evteventdata;
	ObjectAddress myself,
				referenced;

	/* Open pg_event_trigger. */
	tgrel = table_open(EventTriggerRelationId, RowExclusiveLock);

	/* Build the new pg_trigger tuple. */
	trigoid = GetNewOidWithIndex(tgrel, EventTriggerOidIndexId,
								 Anum_pg_event_trigger_oid);
	values[Anum_pg_event_trigger_oid - 1] = ObjectIdGetDatum(trigoid);
	memset(nulls, false, sizeof(nulls));
	namestrcpy(&evtnamedata, trigname);
	values[Anum_pg_event_trigger_evtname - 1] = NameGetDatum(&evtnamedata);
	namestrcpy(&evteventdata, eventname);
	values[Anum_pg_event_trigger_evtevent - 1] = NameGetDatum(&evteventdata);
	values[Anum_pg_event_trigger_evtowner - 1] = ObjectIdGetDatum(evtOwner);
	values[Anum_pg_event_trigger_evtfoid - 1] = ObjectIdGetDatum(funcoid);
	values[Anum_pg_event_trigger_evtenabled - 1] =
		CharGetDatum(TRIGGER_FIRES_ON_ORIGIN);
	if (taglist == NIL)
		nulls[Anum_pg_event_trigger_evttags - 1] = true;
	else
		values[Anum_pg_event_trigger_evttags - 1] =
			filter_list_to_array(taglist);

	/* Insert heap tuple. */
	tuple = heap_form_tuple(tgrel->rd_att, values, nulls);
	CatalogTupleInsert(tgrel, tuple);
	heap_freetuple(tuple);

	/* Depend on owner. */
	recordDependencyOnOwner(EventTriggerRelationId, trigoid, evtOwner);

	/* Depend on event trigger function. */
	myself.classId = EventTriggerRelationId;
	myself.objectId = trigoid;
	myself.objectSubId = 0;
	referenced.classId = ProcedureRelationId;
	referenced.objectId = funcoid;
	referenced.objectSubId = 0;
	recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

	/* Depend on extension, if any. */
	recordDependencyOnCurrentExtension(&myself, false);

	/* Post creation hook for new event trigger */
	InvokeObjectPostCreateHook(EventTriggerRelationId, trigoid, 0);

	/* Close pg_event_trigger. */
	table_close(tgrel, RowExclusiveLock);

	return trigoid;
}