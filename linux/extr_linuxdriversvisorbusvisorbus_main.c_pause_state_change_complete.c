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
struct visor_device {int pausing; } ;

/* Variables and functions */
 int /*<<< orphan*/  segment_state_standby ; 
 int /*<<< orphan*/  visorbus_device_changestate_response (struct visor_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pause_state_change_complete(struct visor_device *dev, int status)
{
	if (!dev->pausing)
		return;

	dev->pausing = false;
	visorbus_device_changestate_response(dev, status,
					     segment_state_standby);
}