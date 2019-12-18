#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  attname; scalar_t__ attnotnull; } ;
struct TYPE_4__ {int /*<<< orphan*/  rd_att; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEBUG4 ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXATTR ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int* Nulls ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_1__*) ; 
 TYPE_2__* TupleDescAttr (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* boot_reldesc ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/ * values ; 

void
InsertOneNull(int i)
{
	elog(DEBUG4, "inserting column %d NULL", i);
	Assert(i >= 0 && i < MAXATTR);
	if (TupleDescAttr(boot_reldesc->rd_att, i)->attnotnull)
		elog(ERROR,
			 "NULL value specified for not-null column \"%s\" of relation \"%s\"",
			 NameStr(TupleDescAttr(boot_reldesc->rd_att, i)->attname),
			 RelationGetRelationName(boot_reldesc));
	values[i] = PointerGetDatum(NULL);
	Nulls[i] = true;
}