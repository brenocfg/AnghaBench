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
 int /*<<< orphan*/  ZCG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accel_deactivate_now () ; 
 int /*<<< orphan*/  counted ; 

void accelerator_shm_read_unlock(void)
{
	if (!ZCG(counted)) {
		/* counted is 0 - meaning we had to readlock manually, release readlock now */
		accel_deactivate_now();
	}
}