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
typedef  int u32 ;
struct i1480 {int hw_rev; int (* read ) (struct i1480*,int,int) ;int (* write ) (struct i1480*,int,int*,int) ;int /*<<< orphan*/  dev; scalar_t__ cmd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i1480_FW_UPLOAD_MODE_MASK ; 
 int stub1 (struct i1480*,int,int) ; 
 int stub2 (struct i1480*,int,int*,int) ; 

__attribute__((used)) static
int mac_fw_upload_enable(struct i1480 *i1480)
{
	int result;
	u32 reg = 0x800000c0;
	u32 *buffer = (u32 *)i1480->cmd_buf;

	if (i1480->hw_rev > 1)
		reg = 0x8000d0d4;
	result = i1480->read(i1480, reg, sizeof(u32));
	if (result < 0)
		goto error_cmd;
	*buffer &= ~i1480_FW_UPLOAD_MODE_MASK;
	result = i1480->write(i1480, reg, buffer, sizeof(u32));
	if (result < 0)
		goto error_cmd;
	return 0;
error_cmd:
	dev_err(i1480->dev, "can't enable fw upload mode: %d\n", result);
	return result;
}