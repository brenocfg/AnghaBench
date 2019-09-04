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
struct i1480 {int (* read ) (struct i1480*,int,int) ;int /*<<< orphan*/  dev; scalar_t__ cmd_buf; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct i1480*,int,int) ; 

__attribute__((used)) static
int i1480_fw_is_running_q(struct i1480 *i1480)
{
	int cnt = 0;
	int result;
	u32 *val = (u32 *) i1480->cmd_buf;

	for (cnt = 0; cnt < 10; cnt++) {
		msleep(100);
		result = i1480->read(i1480, 0x80080000, 4);
		if (result < 0) {
			dev_err(i1480->dev, "Can't read 0x8008000: %d\n", result);
			goto out;
		}
		if (*val == 0x55555555UL)	/* fw running? cool */
			goto out;
	}
	dev_err(i1480->dev, "Timed out waiting for fw to start\n");
	result = -ETIMEDOUT;
out:
	return result;

}