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
typedef  int /*<<< orphan*/  pybsleep_wake_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  pybsleep_wake_reason ; 

pybsleep_wake_reason_t pyb_sleep_get_wake_reason (void) {
    return pybsleep_wake_reason;
}