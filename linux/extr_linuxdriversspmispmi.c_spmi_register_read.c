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
struct spmi_device {int /*<<< orphan*/  usid; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPMI_CMD_READ ; 
 int spmi_read_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int) ; 

int spmi_register_read(struct spmi_device *sdev, u8 addr, u8 *buf)
{
	/* 5-bit register address */
	if (addr > 0x1F)
		return -EINVAL;

	return spmi_read_cmd(sdev->ctrl, SPMI_CMD_READ, sdev->usid, addr,
			     buf, 1);
}