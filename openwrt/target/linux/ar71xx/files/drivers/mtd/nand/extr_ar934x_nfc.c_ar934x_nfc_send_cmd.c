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
typedef  unsigned int u32 ;
struct ar934x_nfc {int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 unsigned int AR934X_NFC_CMD_ADDR_SEL_0 ; 
 unsigned int AR934X_NFC_CMD_CMD0_M ; 
 unsigned int AR934X_NFC_CMD_CMD0_S ; 
 unsigned int AR934X_NFC_CMD_INPUT_SEL_SIU ; 
 unsigned int AR934X_NFC_CMD_SEQ_1C ; 
 int /*<<< orphan*/  AR934X_NFC_REG_CTRL ; 
 int /*<<< orphan*/  AR934X_NFC_REG_INT_STATUS ; 
 int /*<<< orphan*/  ar934x_nfc_wait_dev_ready (struct ar934x_nfc*) ; 
 int /*<<< orphan*/  ar934x_nfc_wr (struct ar934x_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar934x_nfc_write_cmd_reg (struct ar934x_nfc*,unsigned int) ; 

__attribute__((used)) static void
ar934x_nfc_send_cmd(struct ar934x_nfc *nfc, unsigned command)
{
	u32 cmd_reg;

	cmd_reg = AR934X_NFC_CMD_INPUT_SEL_SIU | AR934X_NFC_CMD_ADDR_SEL_0 |
		  AR934X_NFC_CMD_SEQ_1C;
	cmd_reg |= (command & AR934X_NFC_CMD_CMD0_M) << AR934X_NFC_CMD_CMD0_S;

	ar934x_nfc_wr(nfc, AR934X_NFC_REG_INT_STATUS, 0);
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_CTRL, nfc->ctrl_reg);

	ar934x_nfc_write_cmd_reg(nfc, cmd_reg);
	ar934x_nfc_wait_dev_ready(nfc);
}