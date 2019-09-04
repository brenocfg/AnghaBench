#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nilfs_palloc_cache {int /*<<< orphan*/  lock; int /*<<< orphan*/  prev_entry; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {struct nilfs_palloc_cache* mi_palloc_cache; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int nilfs_palloc_delete_block (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_palloc_entry_blkoff (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_palloc_delete_entry_block(struct inode *inode, __u64 nr)
{
	struct nilfs_palloc_cache *cache = NILFS_MDT(inode)->mi_palloc_cache;

	return nilfs_palloc_delete_block(inode,
					 nilfs_palloc_entry_blkoff(inode, nr),
					 &cache->prev_entry, &cache->lock);
}