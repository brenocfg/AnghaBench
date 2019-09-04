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
struct timespec64 {int tv_sec; unsigned int tv_nsec; } ;

/* Variables and functions */
 unsigned int NSEC_PER_USEC ; 
 unsigned int USEC_PER_SEC ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 

__attribute__((used)) static inline unsigned int mon_get_timestamp(void)
{
	struct timespec64 now;
	unsigned int stamp;

	ktime_get_ts64(&now);
	stamp = now.tv_sec & 0xFFF;  /* 2^32 = 4294967296. Limit to 4096s. */
	stamp = stamp * USEC_PER_SEC + now.tv_nsec / NSEC_PER_USEC;
	return stamp;
}