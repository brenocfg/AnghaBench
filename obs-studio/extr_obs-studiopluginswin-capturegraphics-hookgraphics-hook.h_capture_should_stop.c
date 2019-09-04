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
typedef  int uint64_t ;

/* Variables and functions */
 scalar_t__ capture_active () ; 
 int capture_alive () ; 
 scalar_t__ capture_stopped () ; 
 int os_gettime_ns () ; 

__attribute__((used)) static inline bool capture_should_stop(void)
{
	bool stop_requested = false;

	if (capture_active()) {
		static uint64_t last_keepalive_check = 0;
		uint64_t cur_time = os_gettime_ns();
		bool alive = true;

		if (cur_time - last_keepalive_check > 5000000000) {
			alive = capture_alive();
			last_keepalive_check = cur_time;
		}

		stop_requested = capture_stopped() || !alive;
	}

	return stop_requested;
}