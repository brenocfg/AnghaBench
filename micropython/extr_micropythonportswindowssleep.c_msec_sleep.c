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
typedef  scalar_t__ __int64 ;

/* Variables and functions */
 scalar_t__ LLONG_MAX ; 
 int /*<<< orphan*/  usleep_impl (scalar_t__) ; 

void msec_sleep(double msec) {
    const double usec = msec * 1000.0;
    usleep_impl(usec > (double)LLONG_MAX ? LLONG_MAX : (__int64)usec);
}