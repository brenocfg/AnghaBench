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
struct timespec64 {int tv_sec; int /*<<< orphan*/  tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_coarse_real_ts64 (struct timespec64*) ; 
 struct timespec64 timespec64_add (struct timespec64,struct timespec64) ; 

__attribute__((used)) static inline struct timespec64 get_expire_time(int ttl)
{
	struct timespec64 ts = {
		.tv_sec = ttl,
		.tv_nsec = 0,
	};
	struct timespec64 now;

	ktime_get_coarse_real_ts64(&now);
	return timespec64_add(now, ts);
}