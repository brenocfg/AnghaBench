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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct smsc9420_pdata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t E2P_CMD_EPC_CMD_READ_ ; 
 int /*<<< orphan*/  E2P_DATA ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct smsc9420_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int smsc9420_eeprom_send_cmd (struct smsc9420_pdata*,size_t) ; 
 size_t smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smsc9420_eeprom_read_location(struct smsc9420_pdata *pd,
					 u8 address, u8 *data)
{
	u32 op = E2P_CMD_EPC_CMD_READ_ | address;
	int ret;

	netif_dbg(pd, hw, pd->dev, "address 0x%x\n", address);
	ret = smsc9420_eeprom_send_cmd(pd, op);

	if (!ret)
		data[address] = smsc9420_reg_read(pd, E2P_DATA);

	return ret;
}