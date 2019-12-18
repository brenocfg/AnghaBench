#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pubtruncate; int /*<<< orphan*/  pubdelete; int /*<<< orphan*/  pubupdate; int /*<<< orphan*/  pubinsert; int /*<<< orphan*/  puballtables; int /*<<< orphan*/  pubname; } ;
struct TYPE_5__ {int /*<<< orphan*/  pubtruncate; int /*<<< orphan*/  pubdelete; int /*<<< orphan*/  pubupdate; int /*<<< orphan*/  pubinsert; } ;
struct TYPE_6__ {TYPE_1__ pubactions; int /*<<< orphan*/  alltables; int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;
typedef  TYPE_2__ Publication ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_publication ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUBLICATIONOID ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 

Publication *
GetPublication(Oid pubid)
{
	HeapTuple	tup;
	Publication *pub;
	Form_pg_publication pubform;

	tup = SearchSysCache1(PUBLICATIONOID, ObjectIdGetDatum(pubid));

	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for publication %u", pubid);

	pubform = (Form_pg_publication) GETSTRUCT(tup);

	pub = (Publication *) palloc(sizeof(Publication));
	pub->oid = pubid;
	pub->name = pstrdup(NameStr(pubform->pubname));
	pub->alltables = pubform->puballtables;
	pub->pubactions.pubinsert = pubform->pubinsert;
	pub->pubactions.pubupdate = pubform->pubupdate;
	pub->pubactions.pubdelete = pubform->pubdelete;
	pub->pubactions.pubtruncate = pubform->pubtruncate;

	ReleaseSysCache(tup);

	return pub;
}