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
struct TYPE_2__ {int rate_bytes_ps; } ;
struct tbf_sched_data {TYPE_1__ peak; } ;

/* Variables and functions */

__attribute__((used)) static bool tbf_peak_present(const struct tbf_sched_data *q)
{
	return q->peak.rate_bytes_ps;
}