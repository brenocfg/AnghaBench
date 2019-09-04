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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SR_RD_REGS ; 
 int /*<<< orphan*/  SR_REQ_RD_REG ; 
 int usbnet_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int sr_read(struct usbnet *dev, u8 reg, u16 length, void *data)
{
	int err;

	err = usbnet_read_cmd(dev, SR_RD_REGS, SR_REQ_RD_REG, 0, reg, data,
			      length);
	if ((err != length) && (err >= 0))
		err = -EINVAL;
	return err;
}