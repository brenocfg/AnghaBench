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
struct ds_device {int dummy; } ;

/* Variables and functions */
 int COMM_1_WIRE_RESET ; 
 int COMM_IM ; 
 int /*<<< orphan*/  SPEED_NORMAL ; 
 int ds_send_control (struct ds_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds_reset(struct ds_device *dev)
{
	int err;

	/* Other potentionally interesting flags for reset.
	 *
	 * COMM_NTF: Return result register feedback.  This could be used to
	 * detect some conditions such as short, alarming presence, or
	 * detect if a new device was detected.
	 *
	 * COMM_SE which allows SPEED_NORMAL, SPEED_FLEXIBLE, SPEED_OVERDRIVE:
	 * Select the data transfer rate.
	 */
	err = ds_send_control(dev, COMM_1_WIRE_RESET | COMM_IM, SPEED_NORMAL);
	if (err)
		return err;

	return 0;
}