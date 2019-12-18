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

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_config_div ; 
 int /*<<< orphan*/  perf_config (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int intel_pt_cache_divisor(void)
{
	static int d;

	if (d)
		return d;

	perf_config(intel_pt_config_div, &d);

	if (!d)
		d = 64;

	return d;
}