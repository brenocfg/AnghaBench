#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct perf_tsc_conversion {int /*<<< orphan*/  time_mult; int /*<<< orphan*/  time_zero; int /*<<< orphan*/  time_shift; } ;
struct jit_buf_desc {TYPE_2__* session; int /*<<< orphan*/  use_arch_timestamp; } ;
struct TYPE_3__ {int /*<<< orphan*/  time_zero; int /*<<< orphan*/  time_mult; int /*<<< orphan*/  time_shift; } ;
struct TYPE_4__ {TYPE_1__ time_conv; } ;

/* Variables and functions */
 int /*<<< orphan*/  tsc_to_perf_time (int /*<<< orphan*/ ,struct perf_tsc_conversion*) ; 

__attribute__((used)) static uint64_t convert_timestamp(struct jit_buf_desc *jd, uint64_t timestamp)
{
	struct perf_tsc_conversion tc;

	if (!jd->use_arch_timestamp)
		return timestamp;

	tc.time_shift = jd->session->time_conv.time_shift;
	tc.time_mult  = jd->session->time_conv.time_mult;
	tc.time_zero  = jd->session->time_conv.time_zero;

	if (!tc.time_mult)
		return 0;

	return tsc_to_perf_time(timestamp, &tc);
}