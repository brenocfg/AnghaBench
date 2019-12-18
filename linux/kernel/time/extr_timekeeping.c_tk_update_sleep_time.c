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
struct timekeeper {int /*<<< orphan*/  offs_boot; int /*<<< orphan*/  monotonic_to_boot; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_timespec64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tk_update_sleep_time(struct timekeeper *tk, ktime_t delta)
{
	tk->offs_boot = ktime_add(tk->offs_boot, delta);
	/*
	 * Timespec representation for VDSO update to avoid 64bit division
	 * on every update.
	 */
	tk->monotonic_to_boot = ktime_to_timespec64(tk->offs_boot);
}