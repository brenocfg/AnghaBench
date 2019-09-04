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
typedef  int /*<<< orphan*/  u32 ;
struct i1480 {int (* read ) (struct i1480*,int,int) ;int /*<<< orphan*/  dev; scalar_t__ cmd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct i1480*,int,int) ; 

__attribute__((used)) static
int i1480_print_state(struct i1480 *i1480)
{
	int result;
	u32 *buf = (u32 *) i1480->cmd_buf;

	result = i1480->read(i1480, 0x80080000, 2 * sizeof(*buf));
	if (result < 0) {
		dev_err(i1480->dev, "cannot read U & L states: %d\n", result);
		goto error;
	}
	dev_info(i1480->dev, "state U 0x%08x, L 0x%08x\n", buf[0], buf[1]);
error:
	return result;
}