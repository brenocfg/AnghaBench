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
struct TYPE_5__ {int /*<<< orphan*/  rel; } ;
typedef  TYPE_1__ PartitionDirectoryEntry ;
typedef  TYPE_2__* PartitionDirectory ;
typedef  int /*<<< orphan*/  HASH_SEQ_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RelationDecrementReferenceCount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_seq_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* hash_seq_search (int /*<<< orphan*/ *) ; 

void
DestroyPartitionDirectory(PartitionDirectory pdir)
{
	HASH_SEQ_STATUS status;
	PartitionDirectoryEntry *pde;

	hash_seq_init(&status, pdir->pdir_hash);
	while ((pde = hash_seq_search(&status)) != NULL)
		RelationDecrementReferenceCount(pde->rel);
}