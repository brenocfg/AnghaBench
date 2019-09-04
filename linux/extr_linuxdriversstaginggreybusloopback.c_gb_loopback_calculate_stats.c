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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct gb_loopback {scalar_t__ iteration_count; scalar_t__ iteration_max; scalar_t__ requests_completed; int /*<<< orphan*/  ts; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ NSEC_PER_SEC ; 
 scalar_t__ gb_loopback_calc_latency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_loopback_calculate_latency_stats (struct gb_loopback*) ; 
 int /*<<< orphan*/  gb_loopback_nsec_to_usec_latency (scalar_t__) ; 
 int /*<<< orphan*/  gb_loopback_requests_update (struct gb_loopback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_loopback_throughput_update (struct gb_loopback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void gb_loopback_calculate_stats(struct gb_loopback *gb, bool error)
{
	u64 nlat;
	u32 lat;
	ktime_t te;

	if (!error) {
		gb->requests_completed++;
		gb_loopback_calculate_latency_stats(gb);
	}

	te = ktime_get();
	nlat = gb_loopback_calc_latency(gb->ts, te);
	if (nlat >= NSEC_PER_SEC || gb->iteration_count == gb->iteration_max) {
		lat = gb_loopback_nsec_to_usec_latency(nlat);

		gb_loopback_throughput_update(gb, lat);
		gb_loopback_requests_update(gb, lat);

		if (gb->iteration_count != gb->iteration_max) {
			gb->ts = te;
			gb->requests_completed = 0;
		}
	}
}