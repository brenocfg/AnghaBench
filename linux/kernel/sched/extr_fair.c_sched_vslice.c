#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sched_entity {int dummy; } ;
struct cfs_rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_delta_fair (int /*<<< orphan*/ ,struct sched_entity*) ; 
 int /*<<< orphan*/  sched_slice (struct cfs_rq*,struct sched_entity*) ; 

__attribute__((used)) static u64 sched_vslice(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	return calc_delta_fair(sched_slice(cfs_rq, se), se);
}