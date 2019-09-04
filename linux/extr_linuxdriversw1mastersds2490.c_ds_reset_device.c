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
typedef  int u8 ;
struct ds_device {int spu_sleep; } ;

/* Variables and functions */
 int COMM_IM ; 
 int COMM_SET_DURATION ; 
 int /*<<< orphan*/  CTL_RESET_DEVICE ; 
 int /*<<< orphan*/  MOD_PULSE_EN ; 
 int /*<<< orphan*/  PULSE_SPUE ; 
 scalar_t__ ds_send_control (struct ds_device*,int,int) ; 
 int /*<<< orphan*/  ds_send_control_cmd (struct ds_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ds_send_control_mode (struct ds_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void ds_reset_device(struct ds_device *dev)
{
	ds_send_control_cmd(dev, CTL_RESET_DEVICE, 0);
	/* Always allow strong pullup which allow individual writes to use
	 * the strong pullup.
	 */
	if (ds_send_control_mode(dev, MOD_PULSE_EN, PULSE_SPUE))
		pr_err("ds_reset_device: Error allowing strong pullup\n");
	/* Chip strong pullup time was cleared. */
	if (dev->spu_sleep) {
		/* lower 4 bits are 0, see ds_set_pullup */
		u8 del = dev->spu_sleep>>4;
		if (ds_send_control(dev, COMM_SET_DURATION | COMM_IM, del))
			pr_err("ds_reset_device: Error setting duration\n");
	}
}