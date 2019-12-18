#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_12__ {int /*<<< orphan*/  (* smgr_open ) (TYPE_1__*) ;} ;
struct TYPE_11__ {int keysize; int entrysize; } ;
struct TYPE_10__ {int /*<<< orphan*/  backend; int /*<<< orphan*/  node; } ;
struct TYPE_9__ {size_t smgr_which; int /*<<< orphan*/  node; void* smgr_vm_nblocks; void* smgr_fsm_nblocks; void* smgr_targblock; int /*<<< orphan*/ * smgr_owner; } ;
typedef  int /*<<< orphan*/  SMgrRelationData ;
typedef  TYPE_1__* SMgrRelation ;
typedef  TYPE_2__ RelFileNodeBackend ;
typedef  int /*<<< orphan*/  RelFileNode ;
typedef  TYPE_3__ HASHCTL ;
typedef  int /*<<< orphan*/  BackendId ;

/* Variables and functions */
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 void* InvalidBlockNumber ; 
 int /*<<< orphan*/  MemSet (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * SMgrRelationHash ; 
 int /*<<< orphan*/  dlist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_push_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_3__*,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 TYPE_5__* smgrsw ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  unowned_relns ; 

SMgrRelation
smgropen(RelFileNode rnode, BackendId backend)
{
	RelFileNodeBackend brnode;
	SMgrRelation reln;
	bool		found;

	if (SMgrRelationHash == NULL)
	{
		/* First time through: initialize the hash table */
		HASHCTL		ctl;

		MemSet(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(RelFileNodeBackend);
		ctl.entrysize = sizeof(SMgrRelationData);
		SMgrRelationHash = hash_create("smgr relation table", 400,
									   &ctl, HASH_ELEM | HASH_BLOBS);
		dlist_init(&unowned_relns);
	}

	/* Look up or create an entry */
	brnode.node = rnode;
	brnode.backend = backend;
	reln = (SMgrRelation) hash_search(SMgrRelationHash,
									  (void *) &brnode,
									  HASH_ENTER, &found);

	/* Initialize it if not present before */
	if (!found)
	{
		/* hash_search already filled in the lookup key */
		reln->smgr_owner = NULL;
		reln->smgr_targblock = InvalidBlockNumber;
		reln->smgr_fsm_nblocks = InvalidBlockNumber;
		reln->smgr_vm_nblocks = InvalidBlockNumber;
		reln->smgr_which = 0;	/* we only have md.c at present */

		/* implementation-specific initialization */
		smgrsw[reln->smgr_which].smgr_open(reln);

		/* it has no owner yet */
		dlist_push_tail(&unowned_relns, &reln->node);
	}

	return reln;
}