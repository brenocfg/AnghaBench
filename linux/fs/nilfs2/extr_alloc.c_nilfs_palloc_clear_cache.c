#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * bh; } ;
struct TYPE_7__ {int /*<<< orphan*/ * bh; } ;
struct TYPE_6__ {int /*<<< orphan*/ * bh; } ;
struct nilfs_palloc_cache {int /*<<< orphan*/  lock; TYPE_1__ prev_entry; TYPE_3__ prev_bitmap; TYPE_2__ prev_desc; } ;
struct inode {int dummy; } ;
struct TYPE_8__ {struct nilfs_palloc_cache* mi_palloc_cache; } ;

/* Variables and functions */
 TYPE_4__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nilfs_palloc_clear_cache(struct inode *inode)
{
	struct nilfs_palloc_cache *cache = NILFS_MDT(inode)->mi_palloc_cache;

	spin_lock(&cache->lock);
	brelse(cache->prev_desc.bh);
	brelse(cache->prev_bitmap.bh);
	brelse(cache->prev_entry.bh);
	cache->prev_desc.bh = NULL;
	cache->prev_bitmap.bh = NULL;
	cache->prev_entry.bh = NULL;
	spin_unlock(&cache->lock);
}