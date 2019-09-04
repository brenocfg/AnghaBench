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
struct super_block {int cleancache_poolid; int /*<<< orphan*/  s_uuid; } ;
struct TYPE_2__ {int (* init_shared_fs ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CLEANCACHE_NO_BACKEND_SHARED ; 
 int CLEANCACHE_NO_POOL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__* cleancache_ops ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __cleancache_init_shared_fs(struct super_block *sb)
{
	int pool_id = CLEANCACHE_NO_BACKEND_SHARED;

	if (cleancache_ops) {
		pool_id = cleancache_ops->init_shared_fs(&sb->s_uuid, PAGE_SIZE);
		if (pool_id < 0)
			pool_id = CLEANCACHE_NO_POOL;
	}
	sb->cleancache_poolid = pool_id;
}