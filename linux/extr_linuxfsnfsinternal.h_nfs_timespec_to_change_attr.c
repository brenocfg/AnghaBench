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
typedef  int u64 ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static inline
u64 nfs_timespec_to_change_attr(const struct timespec *ts)
{
	return ((u64)ts->tv_sec << 30) + ts->tv_nsec;
}