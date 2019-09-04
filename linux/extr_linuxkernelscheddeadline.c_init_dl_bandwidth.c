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
typedef  void* u64 ;
struct dl_bandwidth {void* dl_runtime; void* dl_period; int /*<<< orphan*/  dl_runtime_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

void init_dl_bandwidth(struct dl_bandwidth *dl_b, u64 period, u64 runtime)
{
	raw_spin_lock_init(&dl_b->dl_runtime_lock);
	dl_b->dl_period = period;
	dl_b->dl_runtime = runtime;
}