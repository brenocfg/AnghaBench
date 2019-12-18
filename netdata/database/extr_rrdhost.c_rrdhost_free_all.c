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
 scalar_t__ localhost ; 
 int /*<<< orphan*/  rrd_unlock () ; 
 int /*<<< orphan*/  rrd_wrlock () ; 
 int /*<<< orphan*/  rrdhost_free (scalar_t__) ; 

void rrdhost_free_all(void) {
    rrd_wrlock();
    while(localhost) rrdhost_free(localhost);
    rrd_unlock();
}