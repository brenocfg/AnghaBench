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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_7__ {int /*<<< orphan*/  attcollation; } ;
struct TYPE_6__ {int natts; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  AssertArg (int) ; 
 int PointerIsValid (TYPE_1__*) ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 

void
TupleDescInitEntryCollation(TupleDesc desc,
							AttrNumber attributeNumber,
							Oid collationid)
{
	/*
	 * sanity checks
	 */
	AssertArg(PointerIsValid(desc));
	AssertArg(attributeNumber >= 1);
	AssertArg(attributeNumber <= desc->natts);

	TupleDescAttr(desc, attributeNumber - 1)->attcollation = collationid;
}