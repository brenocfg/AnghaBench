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
struct ast_vhub {int /*<<< orphan*/  wake_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void ast_vhub_hub_wake_all(struct ast_vhub *vhub)
{
	/*
	 * A device is trying to wake the world, because this
	 * can recurse into the device, we break the call chain
	 * using a work queue
	 */
	schedule_work(&vhub->wake_work);
}