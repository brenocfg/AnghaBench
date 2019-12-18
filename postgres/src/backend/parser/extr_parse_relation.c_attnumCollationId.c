#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int natts; } ;
struct TYPE_6__ {int /*<<< orphan*/  attcollation; } ;
struct TYPE_5__ {TYPE_4__* rd_att; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 TYPE_3__* TupleDescAttr (TYPE_4__*,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 

Oid
attnumCollationId(Relation rd, int attid)
{
	if (attid <= 0)
	{
		/* All system attributes are of noncollatable types. */
		return InvalidOid;
	}
	if (attid > rd->rd_att->natts)
		elog(ERROR, "invalid attribute number %d", attid);
	return TupleDescAttr(rd->rd_att, attid - 1)->attcollation;
}