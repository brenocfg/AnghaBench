#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct serio {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  nvec; } ;

/* Variables and functions */
 int ENABLE_MOUSE ; 
 int NVEC_PS2 ; 
 int SEND_COMMAND ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned char) ; 
 int nvec_write_async (int /*<<< orphan*/ ,unsigned char*,int) ; 
 TYPE_1__ ps2_dev ; 

__attribute__((used)) static int ps2_sendcommand(struct serio *ser_dev, unsigned char cmd)
{
	unsigned char buf[] = { NVEC_PS2, SEND_COMMAND, ENABLE_MOUSE, 1 };

	buf[2] = cmd & 0xff;

	dev_dbg(&ser_dev->dev, "Sending ps2 cmd %02x\n", cmd);
	return nvec_write_async(ps2_dev.nvec, buf, sizeof(buf));
}