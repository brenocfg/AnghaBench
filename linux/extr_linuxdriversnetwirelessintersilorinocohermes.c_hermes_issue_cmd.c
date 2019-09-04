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
typedef  int u16 ;
struct hermes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD ; 
 int CMD_BUSY_TIMEOUT ; 
 int EBUSY ; 
 int HERMES_CMD_BUSY ; 
 int /*<<< orphan*/  PARAM0 ; 
 int /*<<< orphan*/  PARAM1 ; 
 int /*<<< orphan*/  PARAM2 ; 
 int hermes_read_regn (struct hermes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hermes_write_regn (struct hermes*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int hermes_issue_cmd(struct hermes *hw, u16 cmd, u16 param0,
			    u16 param1, u16 param2)
{
	int k = CMD_BUSY_TIMEOUT;
	u16 reg;

	/* First wait for the command register to unbusy */
	reg = hermes_read_regn(hw, CMD);
	while ((reg & HERMES_CMD_BUSY) && k) {
		k--;
		udelay(1);
		reg = hermes_read_regn(hw, CMD);
	}
	if (reg & HERMES_CMD_BUSY)
		return -EBUSY;

	hermes_write_regn(hw, PARAM2, param2);
	hermes_write_regn(hw, PARAM1, param1);
	hermes_write_regn(hw, PARAM0, param0);
	hermes_write_regn(hw, CMD, cmd);

	return 0;
}