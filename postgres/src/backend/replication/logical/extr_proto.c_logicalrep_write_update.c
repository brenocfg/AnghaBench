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
struct TYPE_7__ {TYPE_1__* rd_rel; } ;
struct TYPE_6__ {scalar_t__ relreplident; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/ * HeapTuple ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ REPLICA_IDENTITY_DEFAULT ; 
 scalar_t__ REPLICA_IDENTITY_FULL ; 
 scalar_t__ REPLICA_IDENTITY_INDEX ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  logicalrep_write_tuple (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pq_sendbyte (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
logicalrep_write_update(StringInfo out, Relation rel, HeapTuple oldtuple,
						HeapTuple newtuple)
{
	pq_sendbyte(out, 'U');		/* action UPDATE */

	Assert(rel->rd_rel->relreplident == REPLICA_IDENTITY_DEFAULT ||
		   rel->rd_rel->relreplident == REPLICA_IDENTITY_FULL ||
		   rel->rd_rel->relreplident == REPLICA_IDENTITY_INDEX);

	/* use Oid as relation identifier */
	pq_sendint32(out, RelationGetRelid(rel));

	if (oldtuple != NULL)
	{
		if (rel->rd_rel->relreplident == REPLICA_IDENTITY_FULL)
			pq_sendbyte(out, 'O');	/* old tuple follows */
		else
			pq_sendbyte(out, 'K');	/* old key follows */
		logicalrep_write_tuple(out, rel, oldtuple);
	}

	pq_sendbyte(out, 'N');		/* new tuple follows */
	logicalrep_write_tuple(out, rel, newtuple);
}