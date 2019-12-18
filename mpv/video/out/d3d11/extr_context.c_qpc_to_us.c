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
struct ra_swapchain {struct priv* priv; } ;
struct priv {int perf_freq; } ;
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t qpc_to_us(struct ra_swapchain *sw, int64_t qpc)
{
    struct priv *p = sw->priv;

    // Convert QPC units (1/perf_freq seconds) to microseconds. This will work
    // without overflow because the QPC value is guaranteed not to roll-over
    // within 100 years, so perf_freq must be less than 2.9*10^9.
    return qpc / p->perf_freq * 1000000 +
        qpc % p->perf_freq * 1000000 / p->perf_freq;
}