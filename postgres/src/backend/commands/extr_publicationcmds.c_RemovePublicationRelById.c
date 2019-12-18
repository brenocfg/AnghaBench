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
struct TYPE_8__ {int /*<<< orphan*/  prrelid; } ;
struct TYPE_7__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_publication_rel ;

/* Variables and functions */
 int /*<<< orphan*/  CacheInvalidateRelcacheByRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUBLICATIONREL ; 
 int /*<<< orphan*/  PublicationRelRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemovePublicationRelById(Oid proid)
{
	Relation	rel;
	HeapTuple	tup;
	Form_pg_publication_rel pubrel;

	rel = table_open(PublicationRelRelationId, RowExclusiveLock);

	tup = SearchSysCache1(PUBLICATIONREL, ObjectIdGetDatum(proid));

	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for publication table %u",
			 proid);

	pubrel = (Form_pg_publication_rel) GETSTRUCT(tup);

	/* Invalidate relcache so that publication info is rebuilt. */
	CacheInvalidateRelcacheByRelid(pubrel->prrelid);

	CatalogTupleDelete(rel, &tup->t_self);

	ReleaseSysCache(tup);

	table_close(rel, RowExclusiveLock);
}