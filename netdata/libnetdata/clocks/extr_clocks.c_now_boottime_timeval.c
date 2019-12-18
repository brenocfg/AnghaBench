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
struct timeval {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_BOOTTIME ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  clock_boottime_valid ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int now_timeval (int /*<<< orphan*/ ,struct timeval*) ; 

inline int now_boottime_timeval(struct timeval *tv) {
    return now_timeval(likely(clock_boottime_valid) ? CLOCK_BOOTTIME : CLOCK_MONOTONIC, tv);
}