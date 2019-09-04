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
struct srp_rport {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __srp_start_tl_fail_timers (struct srp_rport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void srp_start_tl_fail_timers(struct srp_rport *rport)
{
	mutex_lock(&rport->mutex);
	__srp_start_tl_fail_timers(rport);
	mutex_unlock(&rport->mutex);
}