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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_TYPE_SOFTWARE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  do_perf_sw_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct perf_sample_data*,struct pt_regs*) ; 
 int /*<<< orphan*/  perf_sample_data_init (struct perf_sample_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ___perf_sw_event(u32 event_id, u64 nr, struct pt_regs *regs, u64 addr)
{
	struct perf_sample_data data;

	if (WARN_ON_ONCE(!regs))
		return;

	perf_sample_data_init(&data, addr, 0);
	do_perf_sw_event(PERF_TYPE_SOFTWARE, event_id, nr, &data, regs);
}