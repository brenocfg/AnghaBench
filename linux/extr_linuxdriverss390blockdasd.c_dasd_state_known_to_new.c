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
struct dasd_device {scalar_t__ block; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STATE_NEW ; 
 int /*<<< orphan*/  dasd_eer_disable (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_free_queue (scalar_t__) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 

__attribute__((used)) static int dasd_state_known_to_new(struct dasd_device *device)
{
	/* Disable extended error reporting for this device. */
	dasd_eer_disable(device);
	device->state = DASD_STATE_NEW;

	if (device->block)
		dasd_free_queue(device->block);

	/* Give up reference we took in dasd_state_new_to_known. */
	dasd_put_device(device);
	return 0;
}