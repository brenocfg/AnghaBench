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
struct super_block {int cleancache_poolid; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* invalidate_fs ) (int) ;} ;

/* Variables and functions */
 int CLEANCACHE_NO_POOL ; 
 TYPE_1__* cleancache_ops ; 
 int /*<<< orphan*/  stub1 (int) ; 

void __cleancache_invalidate_fs(struct super_block *sb)
{
	int pool_id;

	pool_id = sb->cleancache_poolid;
	sb->cleancache_poolid = CLEANCACHE_NO_POOL;

	if (cleancache_ops && pool_id >= 0)
		cleancache_ops->invalidate_fs(pool_id);
}