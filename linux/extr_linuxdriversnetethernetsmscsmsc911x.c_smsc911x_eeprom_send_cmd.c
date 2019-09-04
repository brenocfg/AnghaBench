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
struct smsc911x_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_CMD ; 
 int E2P_CMD_EPC_BUSY_ ; 
 int E2P_CMD_EPC_TIMEOUT_ ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SMSC_WARN (struct smsc911x_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  msleep (int) ; 
 int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc911x_eeprom_send_cmd(struct smsc911x_data *pdata, u32 op)
{
	int timeout = 100;
	u32 e2cmd;

	SMSC_TRACE(pdata, drv, "op 0x%08x", op);
	if (smsc911x_reg_read(pdata, E2P_CMD) & E2P_CMD_EPC_BUSY_) {
		SMSC_WARN(pdata, drv, "Busy at start");
		return -EBUSY;
	}

	e2cmd = op | E2P_CMD_EPC_BUSY_;
	smsc911x_reg_write(pdata, E2P_CMD, e2cmd);

	do {
		msleep(1);
		e2cmd = smsc911x_reg_read(pdata, E2P_CMD);
	} while ((e2cmd & E2P_CMD_EPC_BUSY_) && (--timeout));

	if (!timeout) {
		SMSC_TRACE(pdata, drv, "TIMED OUT");
		return -EAGAIN;
	}

	if (e2cmd & E2P_CMD_EPC_TIMEOUT_) {
		SMSC_TRACE(pdata, drv, "Error occurred during eeprom operation");
		return -EINVAL;
	}

	return 0;
}