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
struct TYPE_7__ {scalar_t__ options; int /*<<< orphan*/  pubname; } ;
struct TYPE_6__ {int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_publication ;
typedef  TYPE_2__ AlterPublicationStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  AlterPublicationOptions (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AlterPublicationTables (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJECT_PUBLICATION ; 
 int /*<<< orphan*/  PUBLICATIONNAME ; 
 int /*<<< orphan*/  PublicationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_publication_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AlterPublication(AlterPublicationStmt *stmt)
{
	Relation	rel;
	HeapTuple	tup;
	Form_pg_publication pubform;

	rel = table_open(PublicationRelationId, RowExclusiveLock);

	tup = SearchSysCacheCopy1(PUBLICATIONNAME,
							  CStringGetDatum(stmt->pubname));

	if (!HeapTupleIsValid(tup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("publication \"%s\" does not exist",
						stmt->pubname)));

	pubform = (Form_pg_publication) GETSTRUCT(tup);

	/* must be owner */
	if (!pg_publication_ownercheck(pubform->oid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_PUBLICATION,
					   stmt->pubname);

	if (stmt->options)
		AlterPublicationOptions(stmt, rel, tup);
	else
		AlterPublicationTables(stmt, rel, tup);

	/* Cleanup. */
	heap_freetuple(tup);
	table_close(rel, RowExclusiveLock);
}