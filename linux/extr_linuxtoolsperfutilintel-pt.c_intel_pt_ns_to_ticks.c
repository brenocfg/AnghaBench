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
typedef  int u64 ;
struct TYPE_2__ {int time_mult; int time_shift; } ;
struct intel_pt {TYPE_1__ tc; } ;

/* Variables and functions */

__attribute__((used)) static u64 intel_pt_ns_to_ticks(const struct intel_pt *pt, u64 ns)
{
	u64 quot, rem;

	quot = ns / pt->tc.time_mult;
	rem  = ns % pt->tc.time_mult;
	return (quot << pt->tc.time_shift) + (rem << pt->tc.time_shift) /
		pt->tc.time_mult;
}