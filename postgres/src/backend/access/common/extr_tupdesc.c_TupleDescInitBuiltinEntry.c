#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_8__ {int attstattarget; int attcacheoff; int attnum; int attndims; int attnotnull; int atthasdef; int atthasmissing; char attidentity; char attgenerated; int attisdropped; int attislocal; int atttypid; int attlen; int attbyval; char attalign; char attstorage; void* attcollation; scalar_t__ attinhcount; int /*<<< orphan*/  atttypmod; int /*<<< orphan*/  attname; scalar_t__ attrelid; } ;
struct TYPE_7__ {int natts; } ;
typedef  int Oid ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AssertArg (int) ; 
#define  BOOLOID 132 
 void* DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERROR ; 
 int FLOAT8PASSBYVAL ; 
#define  INT4OID 131 
#define  INT8OID 130 
 void* InvalidOid ; 
 int PointerIsValid (TYPE_1__*) ; 
#define  TEXTARRAYOID 129 
#define  TEXTOID 128 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 

void
TupleDescInitBuiltinEntry(TupleDesc desc,
						  AttrNumber attributeNumber,
						  const char *attributeName,
						  Oid oidtypeid,
						  int32 typmod,
						  int attdim)
{
	Form_pg_attribute att;

	/* sanity checks */
	AssertArg(PointerIsValid(desc));
	AssertArg(attributeNumber >= 1);
	AssertArg(attributeNumber <= desc->natts);

	/* initialize the attribute fields */
	att = TupleDescAttr(desc, attributeNumber - 1);
	att->attrelid = 0;			/* dummy value */

	/* unlike TupleDescInitEntry, we require an attribute name */
	Assert(attributeName != NULL);
	namestrcpy(&(att->attname), attributeName);

	att->attstattarget = -1;
	att->attcacheoff = -1;
	att->atttypmod = typmod;

	att->attnum = attributeNumber;
	att->attndims = attdim;

	att->attnotnull = false;
	att->atthasdef = false;
	att->atthasmissing = false;
	att->attidentity = '\0';
	att->attgenerated = '\0';
	att->attisdropped = false;
	att->attislocal = true;
	att->attinhcount = 0;
	/* attacl, attoptions and attfdwoptions are not present in tupledescs */

	att->atttypid = oidtypeid;

	/*
	 * Our goal here is to support just enough types to let basic builtin
	 * commands work without catalog access - e.g. so that we can do certain
	 * things even in processes that are not connected to a database.
	 */
	switch (oidtypeid)
	{
		case TEXTOID:
		case TEXTARRAYOID:
			att->attlen = -1;
			att->attbyval = false;
			att->attalign = 'i';
			att->attstorage = 'x';
			att->attcollation = DEFAULT_COLLATION_OID;
			break;

		case BOOLOID:
			att->attlen = 1;
			att->attbyval = true;
			att->attalign = 'c';
			att->attstorage = 'p';
			att->attcollation = InvalidOid;
			break;

		case INT4OID:
			att->attlen = 4;
			att->attbyval = true;
			att->attalign = 'i';
			att->attstorage = 'p';
			att->attcollation = InvalidOid;
			break;

		case INT8OID:
			att->attlen = 8;
			att->attbyval = FLOAT8PASSBYVAL;
			att->attalign = 'd';
			att->attstorage = 'p';
			att->attcollation = InvalidOid;
			break;

		default:
			elog(ERROR, "unsupported type %u", oidtypeid);
	}
}