#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  rd_smgr; TYPE_1__* rd_rel; } ;
struct TYPE_8__ {int /*<<< orphan*/  reltoastrelid; } ;
typedef  TYPE_2__* Relation ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  FlushRelationBuffers (TYPE_2__*) ; 
 int /*<<< orphan*/  MAIN_FORKNUM ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationNeedsWAL (TYPE_2__*) ; 
 int /*<<< orphan*/  smgrimmedsync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
heap_sync(Relation rel)
{
	/* non-WAL-logged tables never need fsync */
	if (!RelationNeedsWAL(rel))
		return;

	/* main heap */
	FlushRelationBuffers(rel);
	/* FlushRelationBuffers will have opened rd_smgr */
	smgrimmedsync(rel->rd_smgr, MAIN_FORKNUM);

	/* FSM is not critical, don't bother syncing it */

	/* toast heap, if any */
	if (OidIsValid(rel->rd_rel->reltoastrelid))
	{
		Relation	toastrel;

		toastrel = table_open(rel->rd_rel->reltoastrelid, AccessShareLock);
		FlushRelationBuffers(toastrel);
		smgrimmedsync(toastrel->rd_smgr, MAIN_FORKNUM);
		table_close(toastrel, AccessShareLock);
	}
}