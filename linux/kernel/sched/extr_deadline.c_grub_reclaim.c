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
typedef  scalar_t__ u64 ;
struct sched_dl_entity {scalar_t__ dl_bw; } ;
struct TYPE_2__ {scalar_t__ this_bw; scalar_t__ running_bw; scalar_t__ bw_ratio; scalar_t__ extra_bw; } ;
struct rq {TYPE_1__ dl; } ;

/* Variables and functions */
 scalar_t__ BW_SHIFT ; 
 scalar_t__ BW_UNIT ; 
 scalar_t__ RATIO_SHIFT ; 

__attribute__((used)) static u64 grub_reclaim(u64 delta, struct rq *rq, struct sched_dl_entity *dl_se)
{
	u64 u_inact = rq->dl.this_bw - rq->dl.running_bw; /* Utot - Uact */
	u64 u_act;
	u64 u_act_min = (dl_se->dl_bw * rq->dl.bw_ratio) >> RATIO_SHIFT;

	/*
	 * Instead of computing max{u * bw_ratio, (1 - u_inact - u_extra)},
	 * we compare u_inact + rq->dl.extra_bw with
	 * 1 - (u * rq->dl.bw_ratio >> RATIO_SHIFT), because
	 * u_inact + rq->dl.extra_bw can be larger than
	 * 1 * (so, 1 - u_inact - rq->dl.extra_bw would be negative
	 * leading to wrong results)
	 */
	if (u_inact + rq->dl.extra_bw > BW_UNIT - u_act_min)
		u_act = u_act_min;
	else
		u_act = BW_UNIT - u_inact - rq->dl.extra_bw;

	return (delta * u_act) >> BW_SHIFT;
}