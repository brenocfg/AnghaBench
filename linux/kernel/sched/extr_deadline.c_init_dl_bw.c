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
struct dl_bw {int bw; scalar_t__ total_bw; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dl_runtime_lock; } ;

/* Variables and functions */
 scalar_t__ RUNTIME_INF ; 
 TYPE_1__ def_dl_bandwidth ; 
 int /*<<< orphan*/  global_rt_period () ; 
 scalar_t__ global_rt_runtime () ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int to_ratio (int /*<<< orphan*/ ,scalar_t__) ; 

void init_dl_bw(struct dl_bw *dl_b)
{
	raw_spin_lock_init(&dl_b->lock);
	raw_spin_lock(&def_dl_bandwidth.dl_runtime_lock);
	if (global_rt_runtime() == RUNTIME_INF)
		dl_b->bw = -1;
	else
		dl_b->bw = to_ratio(global_rt_period(), global_rt_runtime());
	raw_spin_unlock(&def_dl_bandwidth.dl_runtime_lock);
	dl_b->total_bw = 0;
}