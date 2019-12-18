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
struct TYPE_6__ {int /*<<< orphan*/  pdir_hash; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pd; int /*<<< orphan*/  rel; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ PartitionDirectoryEntry ;
typedef  TYPE_2__* PartitionDirectory ;
typedef  int /*<<< orphan*/ * PartitionDesc ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/ * RelationGetPartitionDesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationIncrementReferenceCount (int /*<<< orphan*/ ) ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

PartitionDesc
PartitionDirectoryLookup(PartitionDirectory pdir, Relation rel)
{
	PartitionDirectoryEntry *pde;
	Oid			relid = RelationGetRelid(rel);
	bool		found;

	pde = hash_search(pdir->pdir_hash, &relid, HASH_ENTER, &found);
	if (!found)
	{
		/*
		 * We must keep a reference count on the relation so that the
		 * PartitionDesc to which we are pointing can't get destroyed.
		 */
		RelationIncrementReferenceCount(rel);
		pde->rel = rel;
		pde->pd = RelationGetPartitionDesc(rel);
		Assert(pde->pd != NULL);
	}
	return pde->pd;
}