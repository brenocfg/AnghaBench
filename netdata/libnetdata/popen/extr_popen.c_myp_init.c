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

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  myp_lock ; 
 int myp_tracking ; 
 scalar_t__ netdata_mutex_init (int /*<<< orphan*/ *) ; 

void myp_init(void) {
    info("process tracking enabled.");
    myp_tracking = 1;

    if (netdata_mutex_init(&myp_lock) != 0) {
	fatal("myp_init() mutex init failed.");
    }
}