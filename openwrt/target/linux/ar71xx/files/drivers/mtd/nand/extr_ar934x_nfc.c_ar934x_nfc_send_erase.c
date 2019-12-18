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
struct ar934x_nfc {int ctrl_reg; int addr_count0; scalar_t__ small_page; } ;

/* Variables and functions */
 int AR934X_NFC_CMD_CMD0_S ; 
 unsigned int AR934X_NFC_CMD_CMD1_S ; 
 int AR934X_NFC_CMD_SEQ_ERASE ; 
 int AR934X_NFC_CTRL_ADDR_CYCLE0_M ; 
 int AR934X_NFC_CTRL_ADDR_CYCLE0_S ; 
 int AR934X_NFC_CTRL_ADDR_CYCLE1_M ; 
 int AR934X_NFC_CTRL_ADDR_CYCLE1_S ; 
 int AR934X_NFC_CTRL_SMALL_PAGE ; 
 int /*<<< orphan*/  AR934X_NFC_REG_ADDR0_0 ; 
 int /*<<< orphan*/  AR934X_NFC_REG_ADDR0_1 ; 
 int /*<<< orphan*/  AR934X_NFC_REG_CTRL ; 
 int /*<<< orphan*/  AR934X_NFC_REG_INT_STATUS ; 
 int NAND_CMD_ERASE1 ; 
 int /*<<< orphan*/  ar934x_nfc_get_addr (struct ar934x_nfc*,int,int,int*,int*) ; 
 int /*<<< orphan*/  ar934x_nfc_wait_dev_ready (struct ar934x_nfc*) ; 
 int /*<<< orphan*/  ar934x_nfc_wr (struct ar934x_nfc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar934x_nfc_write_cmd_reg (struct ar934x_nfc*,int) ; 
 int /*<<< orphan*/  nfc_dbg (struct ar934x_nfc*,char*,int,int,int,int,int) ; 

__attribute__((used)) static void
ar934x_nfc_send_erase(struct ar934x_nfc *nfc, unsigned command, int column,
		      int page_addr)
{
	u32 addr0, addr1;
	u32 ctrl_reg;
	u32 cmd_reg;

	ar934x_nfc_get_addr(nfc, column, page_addr, &addr0, &addr1);

	ctrl_reg = nfc->ctrl_reg;
	if (nfc->small_page) {
		/* override number of address cycles for the erase command */
		ctrl_reg &= ~(AR934X_NFC_CTRL_ADDR_CYCLE0_M <<
			      AR934X_NFC_CTRL_ADDR_CYCLE0_S);
		ctrl_reg &= ~(AR934X_NFC_CTRL_ADDR_CYCLE1_M <<
			      AR934X_NFC_CTRL_ADDR_CYCLE1_S);
		ctrl_reg &= ~(AR934X_NFC_CTRL_SMALL_PAGE);
		ctrl_reg |= (nfc->addr_count0 + 1) <<
			    AR934X_NFC_CTRL_ADDR_CYCLE0_S;
	}

	cmd_reg = NAND_CMD_ERASE1 << AR934X_NFC_CMD_CMD0_S;
	cmd_reg |= command << AR934X_NFC_CMD_CMD1_S;
	cmd_reg |= AR934X_NFC_CMD_SEQ_ERASE;

	nfc_dbg(nfc, "erase page %d, a0:%08x a1:%08x cmd:%08x ctrl:%08x\n",
		page_addr, addr0, addr1, cmd_reg, ctrl_reg);

	ar934x_nfc_wr(nfc, AR934X_NFC_REG_INT_STATUS, 0);
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_CTRL, ctrl_reg);
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_ADDR0_0, addr0);
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_ADDR0_1, addr1);

	ar934x_nfc_write_cmd_reg(nfc, cmd_reg);
	ar934x_nfc_wait_dev_ready(nfc);
}