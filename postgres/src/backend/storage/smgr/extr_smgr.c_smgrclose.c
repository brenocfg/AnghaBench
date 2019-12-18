#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* smgr_close ) (TYPE_1__*,scalar_t__) ;} ;
struct TYPE_5__ {size_t smgr_which; int /*<<< orphan*/  smgr_rnode; int /*<<< orphan*/  node; struct TYPE_5__** smgr_owner; } ;
typedef  TYPE_1__* SMgrRelation ;
typedef  scalar_t__ ForkNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_REMOVE ; 
 scalar_t__ MAX_FORKNUM ; 
 int /*<<< orphan*/  SMgrRelationHash ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* smgrsw ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__) ; 

void
smgrclose(SMgrRelation reln)
{
	SMgrRelation *owner;
	ForkNumber	forknum;

	for (forknum = 0; forknum <= MAX_FORKNUM; forknum++)
		smgrsw[reln->smgr_which].smgr_close(reln, forknum);

	owner = reln->smgr_owner;

	if (!owner)
		dlist_delete(&reln->node);

	if (hash_search(SMgrRelationHash,
					(void *) &(reln->smgr_rnode),
					HASH_REMOVE, NULL) == NULL)
		elog(ERROR, "SMgrRelation hashtable corrupted");

	/*
	 * Unhook the owner pointer, if any.  We do this last since in the remote
	 * possibility of failure above, the SMgrRelation object will still exist.
	 */
	if (owner)
		*owner = NULL;
}