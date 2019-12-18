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
struct nilfs_palloc_cache {int /*<<< orphan*/  lock; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct nilfs_palloc_cache* mi_palloc_cache; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void nilfs_palloc_setup_cache(struct inode *inode,
			      struct nilfs_palloc_cache *cache)
{
	NILFS_MDT(inode)->mi_palloc_cache = cache;
	spin_lock_init(&cache->lock);
}