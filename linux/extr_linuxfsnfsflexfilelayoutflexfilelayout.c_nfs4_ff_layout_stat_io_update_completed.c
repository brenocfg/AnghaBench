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
struct nfs4_ff_io_stat {void* aggregate_completion_time; void* total_busy_time; int /*<<< orphan*/  bytes_not_delivered; int /*<<< orphan*/  bytes_completed; int /*<<< orphan*/  ops_completed; } ;
struct nfs4_ff_layoutstat {int /*<<< orphan*/  busy_timer; struct nfs4_ff_io_stat io_stat; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 void* ktime_add (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_ff_end_busy_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs4_ff_layout_stat_io_update_completed(struct nfs4_ff_layoutstat *layoutstat,
		__u64 requested,
		__u64 completed,
		ktime_t time_completed,
		ktime_t time_started)
{
	struct nfs4_ff_io_stat *iostat = &layoutstat->io_stat;
	ktime_t completion_time = ktime_sub(time_completed, time_started);
	ktime_t timer;

	iostat->ops_completed++;
	iostat->bytes_completed += completed;
	iostat->bytes_not_delivered += requested - completed;

	timer = nfs4_ff_end_busy_timer(&layoutstat->busy_timer, time_completed);
	iostat->total_busy_time =
			ktime_add(iostat->total_busy_time, timer);
	iostat->aggregate_completion_time =
			ktime_add(iostat->aggregate_completion_time,
					completion_time);
}