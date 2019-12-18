#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_6__ {int /*<<< orphan*/  attname; } ;
struct TYPE_5__ {int natts; } ;
typedef  int /*<<< orphan*/  Relation ;

/* Variables and functions */
 char* NameStr (int /*<<< orphan*/ ) ; 
 TYPE_1__* RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (TYPE_1__*,int) ; 
 int errtablecolname (int /*<<< orphan*/ ,char const*) ; 
 char* get_attname (int /*<<< orphan*/ ,int,int) ; 

int
errtablecol(Relation rel, int attnum)
{
	TupleDesc	reldesc = RelationGetDescr(rel);
	const char *colname;

	/* Use reldesc if it's a user attribute, else consult the catalogs */
	if (attnum > 0 && attnum <= reldesc->natts)
		colname = NameStr(TupleDescAttr(reldesc, attnum - 1)->attname);
	else
		colname = get_attname(RelationGetRelid(rel), attnum, false);

	return errtablecolname(rel, colname);
}