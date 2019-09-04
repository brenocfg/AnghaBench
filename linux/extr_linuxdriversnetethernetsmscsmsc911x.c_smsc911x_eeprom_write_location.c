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
typedef  int u32 ;
struct smsc911x_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_TEST ; 
 int E2P_CMD_EPC_CMD_ERASE_ ; 
 int E2P_CMD_EPC_CMD_WRITE_ ; 
 int /*<<< orphan*/  E2P_DATA ; 
 int /*<<< orphan*/  SMSC_TRACE (struct smsc911x_data*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  drv ; 
 int smsc911x_eeprom_send_cmd (struct smsc911x_data*,int) ; 
 int smsc911x_reg_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_reg_write (struct smsc911x_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smsc911x_eeprom_write_location(struct smsc911x_data *pdata,
					  u8 address, u8 data)
{
	u32 op = E2P_CMD_EPC_CMD_ERASE_ | address;
	u32 temp;
	int ret;

	SMSC_TRACE(pdata, drv, "address 0x%x, data 0x%x", address, data);
	ret = smsc911x_eeprom_send_cmd(pdata, op);

	if (!ret) {
		op = E2P_CMD_EPC_CMD_WRITE_ | address;
		smsc911x_reg_write(pdata, E2P_DATA, (u32)data);

		/* Workaround for hardware read-after-write restriction */
		temp = smsc911x_reg_read(pdata, BYTE_TEST);

		ret = smsc911x_eeprom_send_cmd(pdata, op);
	}

	return ret;
}