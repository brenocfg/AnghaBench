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
struct z3fold_pool {scalar_t__ zpool; TYPE_1__* zpool_ops; } ;
struct TYPE_2__ {int (* evict ) (scalar_t__,unsigned long) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int stub1 (scalar_t__,unsigned long) ; 

__attribute__((used)) static int z3fold_zpool_evict(struct z3fold_pool *pool, unsigned long handle)
{
	if (pool->zpool && pool->zpool_ops && pool->zpool_ops->evict)
		return pool->zpool_ops->evict(pool->zpool, handle);
	else
		return -ENOENT;
}