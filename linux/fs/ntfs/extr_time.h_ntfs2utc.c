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
typedef  int /*<<< orphan*/  u64 ;
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  sle64 ;

/* Variables and functions */
 scalar_t__ NTFS_TIME_OFFSET ; 
 int do_div (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sle64_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline struct timespec64 ntfs2utc(const sle64 time)
{
	struct timespec64 ts;

	/* Subtract the NTFS time offset. */
	u64 t = (u64)(sle64_to_cpu(time) - NTFS_TIME_OFFSET);
	/*
	 * Convert the time to 1-second intervals and the remainder to
	 * 1-nano-second intervals.
	 */
	ts.tv_nsec = do_div(t, 10000000) * 100;
	ts.tv_sec = t;
	return ts;
}