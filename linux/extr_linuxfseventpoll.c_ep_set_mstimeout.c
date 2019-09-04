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
struct timespec64 {long tv_sec; long tv_nsec; } ;

/* Variables and functions */
 long MSEC_PER_SEC ; 
 long NSEC_PER_MSEC ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 
 struct timespec64 timespec64_add_safe (struct timespec64,struct timespec64) ; 

__attribute__((used)) static inline struct timespec64 ep_set_mstimeout(long ms)
{
	struct timespec64 now, ts = {
		.tv_sec = ms / MSEC_PER_SEC,
		.tv_nsec = NSEC_PER_MSEC * (ms % MSEC_PER_SEC),
	};

	ktime_get_ts64(&now);
	return timespec64_add_safe(now, ts);
}