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
struct ar934x_nfc {int* buf; scalar_t__ swap_dma; int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 int AR934X_NFC_CMD_CMD0_S ; 
 int AR934X_NFC_CMD_SEQ_S ; 
 int /*<<< orphan*/  AR934X_NFC_REG_CTRL ; 
 int /*<<< orphan*/  AR934X_NFC_REG_INT_STATUS ; 
 int /*<<< orphan*/  AR934X_NFC_REG_READ_STATUS ; 
 int NAND_CMD_STATUS ; 
 int ar934x_nfc_rr (struct ar934x_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar934x_nfc_wait_dev_ready (struct ar934x_nfc*) ; 
 int /*<<< orphan*/  ar934x_nfc_wr (struct ar934x_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar934x_nfc_write_cmd_reg (struct ar934x_nfc*,int) ; 
 int /*<<< orphan*/  nfc_dbg (struct ar934x_nfc*,char*,int,int) ; 

__attribute__((used)) static void
ar934x_nfc_read_status(struct ar934x_nfc *nfc)
{
	u32 cmd_reg;
	u32 status;

	cmd_reg = NAND_CMD_STATUS << AR934X_NFC_CMD_CMD0_S;
	cmd_reg |= AR934X_NFC_CMD_SEQ_S;

	ar934x_nfc_wr(nfc, AR934X_NFC_REG_INT_STATUS, 0);
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_CTRL, nfc->ctrl_reg);

	ar934x_nfc_write_cmd_reg(nfc, cmd_reg);
	ar934x_nfc_wait_dev_ready(nfc);

	status = ar934x_nfc_rr(nfc, AR934X_NFC_REG_READ_STATUS);

	nfc_dbg(nfc, "read status, cmd:%08x status:%02x\n",
		cmd_reg, (status & 0xff));

	if (nfc->swap_dma)
		nfc->buf[0 ^ 3] = status;
	else
		nfc->buf[0] = status;
}