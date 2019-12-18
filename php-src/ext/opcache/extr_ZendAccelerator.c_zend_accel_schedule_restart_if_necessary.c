#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_accel_restart_reason ;
struct TYPE_2__ {double memory_consumption; double max_wasted_percentage; } ;

/* Variables and functions */
 TYPE_1__ ZCG (int /*<<< orphan*/ ) ; 
 scalar_t__ ZSMMG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accel_directives ; 
 int /*<<< orphan*/  wasted_shared_memory ; 
 int /*<<< orphan*/  zend_accel_schedule_restart (int /*<<< orphan*/ ) ; 

void zend_accel_schedule_restart_if_necessary(zend_accel_restart_reason reason)
{
	if ((((double) ZSMMG(wasted_shared_memory)) / ZCG(accel_directives).memory_consumption) >= ZCG(accel_directives).max_wasted_percentage) {
 		zend_accel_schedule_restart(reason);
	}
}