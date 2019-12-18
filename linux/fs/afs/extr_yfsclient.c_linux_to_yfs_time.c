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
struct timespec64 {int tv_nsec; scalar_t__ tv_sec; } ;
typedef  int s64 ;

/* Variables and functions */

__attribute__((used)) static s64 linux_to_yfs_time(const struct timespec64 *t)
{
	/* Convert to 100ns intervals. */
	return (u64)t->tv_sec * 10000000 + t->tv_nsec/100;
}