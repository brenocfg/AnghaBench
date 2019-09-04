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
struct bbc_i2c_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_all_fans (struct bbc_i2c_bus*) ; 
 int /*<<< orphan*/  destroy_all_temps (struct bbc_i2c_bus*) ; 
 scalar_t__ kenvctrld_task ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 

void bbc_envctrl_cleanup(struct bbc_i2c_bus *bp)
{
	if (kenvctrld_task)
		kthread_stop(kenvctrld_task);

	destroy_all_temps(bp);
	destroy_all_fans(bp);
}