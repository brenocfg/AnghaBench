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
typedef  void* TransactionId ;
struct TYPE_10__ {int relpages; int reltuples; int relispartition; void* reloftype; void* reltype; void* relowner; void* relminmxid; void* relfrozenxid; int /*<<< orphan*/  relallvisible; } ;
struct TYPE_9__ {TYPE_1__* rd_att; TYPE_3__* rd_rel; } ;
struct TYPE_8__ {void* tdtypeid; } ;
typedef  TYPE_2__* Relation ;
typedef  void* Oid ;
typedef  TYPE_3__* Form_pg_class ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  InsertPgClassTuple (TYPE_2__*,TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  RELKIND_INDEX 132 
#define  RELKIND_MATVIEW 131 
#define  RELKIND_RELATION 130 
#define  RELKIND_SEQUENCE 129 
#define  RELKIND_TOASTVALUE 128 

__attribute__((used)) static void
AddNewRelationTuple(Relation pg_class_desc,
					Relation new_rel_desc,
					Oid new_rel_oid,
					Oid new_type_oid,
					Oid reloftype,
					Oid relowner,
					char relkind,
					TransactionId relfrozenxid,
					TransactionId relminmxid,
					Datum relacl,
					Datum reloptions)
{
	Form_pg_class new_rel_reltup;

	/*
	 * first we update some of the information in our uncataloged relation's
	 * relation descriptor.
	 */
	new_rel_reltup = new_rel_desc->rd_rel;

	switch (relkind)
	{
		case RELKIND_RELATION:
		case RELKIND_MATVIEW:
		case RELKIND_INDEX:
		case RELKIND_TOASTVALUE:
			/* The relation is real, but as yet empty */
			new_rel_reltup->relpages = 0;
			new_rel_reltup->reltuples = 0;
			new_rel_reltup->relallvisible = 0;
			break;
		case RELKIND_SEQUENCE:
			/* Sequences always have a known size */
			new_rel_reltup->relpages = 1;
			new_rel_reltup->reltuples = 1;
			new_rel_reltup->relallvisible = 0;
			break;
		default:
			/* Views, etc, have no disk storage */
			new_rel_reltup->relpages = 0;
			new_rel_reltup->reltuples = 0;
			new_rel_reltup->relallvisible = 0;
			break;
	}

	new_rel_reltup->relfrozenxid = relfrozenxid;
	new_rel_reltup->relminmxid = relminmxid;
	new_rel_reltup->relowner = relowner;
	new_rel_reltup->reltype = new_type_oid;
	new_rel_reltup->reloftype = reloftype;

	/* relispartition is always set by updating this tuple later */
	new_rel_reltup->relispartition = false;

	new_rel_desc->rd_att->tdtypeid = new_type_oid;

	/* Now build and insert the tuple */
	InsertPgClassTuple(pg_class_desc, new_rel_desc, new_rel_oid,
					   relacl, reloptions);
}