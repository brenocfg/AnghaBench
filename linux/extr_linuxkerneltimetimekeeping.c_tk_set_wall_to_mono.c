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
struct timespec64 {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct timekeeper {scalar_t__ offs_real; int /*<<< orphan*/  tai_offset; int /*<<< orphan*/  offs_tai; struct timespec64 wall_to_monotonic; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ktime_add (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_normalized_timespec64 (struct timespec64*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ timespec64_to_ktime (struct timespec64) ; 

__attribute__((used)) static void tk_set_wall_to_mono(struct timekeeper *tk, struct timespec64 wtm)
{
	struct timespec64 tmp;

	/*
	 * Verify consistency of: offset_real = -wall_to_monotonic
	 * before modifying anything
	 */
	set_normalized_timespec64(&tmp, -tk->wall_to_monotonic.tv_sec,
					-tk->wall_to_monotonic.tv_nsec);
	WARN_ON_ONCE(tk->offs_real != timespec64_to_ktime(tmp));
	tk->wall_to_monotonic = wtm;
	set_normalized_timespec64(&tmp, -wtm.tv_sec, -wtm.tv_nsec);
	tk->offs_real = timespec64_to_ktime(tmp);
	tk->offs_tai = ktime_add(tk->offs_real, ktime_set(tk->tai_offset, 0));
}