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
struct tee_shm_pool_mgr {TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ destroy_poolmgr; scalar_t__ free; scalar_t__ alloc; } ;

/* Variables and functions */

__attribute__((used)) static bool check_mgr_ops(struct tee_shm_pool_mgr *mgr)
{
	return mgr && mgr->ops && mgr->ops->alloc && mgr->ops->free &&
		mgr->ops->destroy_poolmgr;
}