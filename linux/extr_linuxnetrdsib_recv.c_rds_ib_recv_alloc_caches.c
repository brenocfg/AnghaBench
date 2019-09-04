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
struct TYPE_2__ {int /*<<< orphan*/  percpu; } ;
struct rds_ib_connection {TYPE_1__ i_cache_incs; TYPE_1__ i_cache_frags; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int rds_ib_recv_alloc_cache (TYPE_1__*,int /*<<< orphan*/ ) ; 

int rds_ib_recv_alloc_caches(struct rds_ib_connection *ic, gfp_t gfp)
{
	int ret;

	ret = rds_ib_recv_alloc_cache(&ic->i_cache_incs, gfp);
	if (!ret) {
		ret = rds_ib_recv_alloc_cache(&ic->i_cache_frags, gfp);
		if (ret)
			free_percpu(ic->i_cache_incs.percpu);
	}

	return ret;
}