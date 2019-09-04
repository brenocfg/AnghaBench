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
struct timespec64 {int dummy; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_coarse_real_ts64 (struct timespec64*) ; 

__attribute__((used)) static int posix_get_realtime_coarse(clockid_t which_clock, struct timespec64 *tp)
{
	ktime_get_coarse_real_ts64(tp);
	return 0;
}