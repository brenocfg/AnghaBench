#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  values ;
typedef  int /*<<< orphan*/  nulls ;
struct TYPE_3__ {int attstattarget; int attndims; int atttypmod; int attinhcount; int /*<<< orphan*/  attcollation; int /*<<< orphan*/  attislocal; int /*<<< orphan*/  attisdropped; int /*<<< orphan*/  attgenerated; int /*<<< orphan*/  attidentity; int /*<<< orphan*/  atthasmissing; int /*<<< orphan*/  atthasdef; int /*<<< orphan*/  attnotnull; int /*<<< orphan*/  attalign; int /*<<< orphan*/  attstorage; int /*<<< orphan*/  attbyval; int /*<<< orphan*/  attnum; int /*<<< orphan*/  attlen; int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; int /*<<< orphan*/  attrelid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_attribute ;
typedef  int Datum ;
typedef  int /*<<< orphan*/ * CatalogIndexState ;

/* Variables and functions */
 int Anum_pg_attribute_attacl ; 
 int Anum_pg_attribute_attalign ; 
 int Anum_pg_attribute_attbyval ; 
 int Anum_pg_attribute_attcacheoff ; 
 int Anum_pg_attribute_attcollation ; 
 int Anum_pg_attribute_attfdwoptions ; 
 int Anum_pg_attribute_attgenerated ; 
 int Anum_pg_attribute_atthasdef ; 
 int Anum_pg_attribute_atthasmissing ; 
 int Anum_pg_attribute_attidentity ; 
 int Anum_pg_attribute_attinhcount ; 
 int Anum_pg_attribute_attisdropped ; 
 int Anum_pg_attribute_attislocal ; 
 int Anum_pg_attribute_attlen ; 
 int Anum_pg_attribute_attmissingval ; 
 int Anum_pg_attribute_attname ; 
 int Anum_pg_attribute_attndims ; 
 int Anum_pg_attribute_attnotnull ; 
 int Anum_pg_attribute_attnum ; 
 int Anum_pg_attribute_attoptions ; 
 int Anum_pg_attribute_attrelid ; 
 int Anum_pg_attribute_attstattarget ; 
 int Anum_pg_attribute_attstorage ; 
 int Anum_pg_attribute_atttypid ; 
 int Anum_pg_attribute_atttypmod ; 
 int BoolGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleInsertWithInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int CharGetDatum (int /*<<< orphan*/ ) ; 
 int Int16GetDatum (int /*<<< orphan*/ ) ; 
 int Int32GetDatum (int) ; 
 int NameGetDatum (int /*<<< orphan*/ *) ; 
 int Natts_pg_attribute ; 
 int ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_form_tuple (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

void
InsertPgAttributeTuple(Relation pg_attribute_rel,
					   Form_pg_attribute new_attribute,
					   CatalogIndexState indstate)
{
	Datum		values[Natts_pg_attribute];
	bool		nulls[Natts_pg_attribute];
	HeapTuple	tup;

	/* This is a tad tedious, but way cleaner than what we used to do... */
	memset(values, 0, sizeof(values));
	memset(nulls, false, sizeof(nulls));

	values[Anum_pg_attribute_attrelid - 1] = ObjectIdGetDatum(new_attribute->attrelid);
	values[Anum_pg_attribute_attname - 1] = NameGetDatum(&new_attribute->attname);
	values[Anum_pg_attribute_atttypid - 1] = ObjectIdGetDatum(new_attribute->atttypid);
	values[Anum_pg_attribute_attstattarget - 1] = Int32GetDatum(new_attribute->attstattarget);
	values[Anum_pg_attribute_attlen - 1] = Int16GetDatum(new_attribute->attlen);
	values[Anum_pg_attribute_attnum - 1] = Int16GetDatum(new_attribute->attnum);
	values[Anum_pg_attribute_attndims - 1] = Int32GetDatum(new_attribute->attndims);
	values[Anum_pg_attribute_attcacheoff - 1] = Int32GetDatum(-1);
	values[Anum_pg_attribute_atttypmod - 1] = Int32GetDatum(new_attribute->atttypmod);
	values[Anum_pg_attribute_attbyval - 1] = BoolGetDatum(new_attribute->attbyval);
	values[Anum_pg_attribute_attstorage - 1] = CharGetDatum(new_attribute->attstorage);
	values[Anum_pg_attribute_attalign - 1] = CharGetDatum(new_attribute->attalign);
	values[Anum_pg_attribute_attnotnull - 1] = BoolGetDatum(new_attribute->attnotnull);
	values[Anum_pg_attribute_atthasdef - 1] = BoolGetDatum(new_attribute->atthasdef);
	values[Anum_pg_attribute_atthasmissing - 1] = BoolGetDatum(new_attribute->atthasmissing);
	values[Anum_pg_attribute_attidentity - 1] = CharGetDatum(new_attribute->attidentity);
	values[Anum_pg_attribute_attgenerated - 1] = CharGetDatum(new_attribute->attgenerated);
	values[Anum_pg_attribute_attisdropped - 1] = BoolGetDatum(new_attribute->attisdropped);
	values[Anum_pg_attribute_attislocal - 1] = BoolGetDatum(new_attribute->attislocal);
	values[Anum_pg_attribute_attinhcount - 1] = Int32GetDatum(new_attribute->attinhcount);
	values[Anum_pg_attribute_attcollation - 1] = ObjectIdGetDatum(new_attribute->attcollation);

	/* start out with empty permissions and empty options */
	nulls[Anum_pg_attribute_attacl - 1] = true;
	nulls[Anum_pg_attribute_attoptions - 1] = true;
	nulls[Anum_pg_attribute_attfdwoptions - 1] = true;
	nulls[Anum_pg_attribute_attmissingval - 1] = true;

	tup = heap_form_tuple(RelationGetDescr(pg_attribute_rel), values, nulls);

	/* finally insert the new tuple, update the indexes, and clean up */
	if (indstate != NULL)
		CatalogTupleInsertWithInfo(pg_attribute_rel, tup, indstate);
	else
		CatalogTupleInsert(pg_attribute_rel, tup);

	heap_freetuple(tup);
}