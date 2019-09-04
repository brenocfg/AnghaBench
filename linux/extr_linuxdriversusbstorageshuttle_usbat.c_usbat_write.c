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
struct us_data {int /*<<< orphan*/  send_ctrl_pipe; } ;

/* Variables and functions */
 unsigned char USBAT_CMD_WRITE_REG ; 
 int /*<<< orphan*/  short_pack (unsigned char,unsigned char) ; 
 int usb_stor_ctrl_transfer (struct us_data*,int /*<<< orphan*/ ,unsigned char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbat_write(struct us_data *us,
		       unsigned char access,
		       unsigned char reg,
		       unsigned char content)
{
	return usb_stor_ctrl_transfer(us,
		us->send_ctrl_pipe,
		access | USBAT_CMD_WRITE_REG,
		0x40,
		short_pack(reg, content),
		0,
		NULL,
		0);
}