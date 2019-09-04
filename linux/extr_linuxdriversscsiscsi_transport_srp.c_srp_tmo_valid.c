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
 int EINVAL ; 
 long HZ ; 
 long LONG_MAX ; 
 int SCSI_DEVICE_BLOCK_MAX_TIMEOUT ; 

int srp_tmo_valid(int reconnect_delay, int fast_io_fail_tmo, long dev_loss_tmo)
{
	if (reconnect_delay < 0 && fast_io_fail_tmo < 0 && dev_loss_tmo < 0)
		return -EINVAL;
	if (reconnect_delay == 0)
		return -EINVAL;
	if (fast_io_fail_tmo > SCSI_DEVICE_BLOCK_MAX_TIMEOUT)
		return -EINVAL;
	if (fast_io_fail_tmo < 0 &&
	    dev_loss_tmo > SCSI_DEVICE_BLOCK_MAX_TIMEOUT)
		return -EINVAL;
	if (dev_loss_tmo >= LONG_MAX / HZ)
		return -EINVAL;
	if (fast_io_fail_tmo >= 0 && dev_loss_tmo >= 0 &&
	    fast_io_fail_tmo >= dev_loss_tmo)
		return -EINVAL;
	return 0;
}