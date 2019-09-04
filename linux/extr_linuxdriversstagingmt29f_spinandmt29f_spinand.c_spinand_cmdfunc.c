#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct spinand_state {int buf_ptr; int* buf; int col; int row; } ;
struct spinand_info {TYPE_1__* spi; struct spinand_state* priv; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  NAND_CMD_ERASE1 139 
#define  NAND_CMD_ERASE2 138 
#define  NAND_CMD_PAGEPROG 137 
#define  NAND_CMD_PARAM 136 
#define  NAND_CMD_READ0 135 
#define  NAND_CMD_READ1 134 
#define  NAND_CMD_READID 133 
#define  NAND_CMD_READOOB 132 
#define  NAND_CMD_RESET 131 
#define  NAND_CMD_RNDOUT 130 
#define  NAND_CMD_SEQIN 129 
#define  NAND_CMD_STATUS 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct spinand_info* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  spinand_erase_block (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spinand_get_otp (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  spinand_program_page (TYPE_1__*,int,int,int,int*) ; 
 int /*<<< orphan*/  spinand_read_id (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  spinand_read_page (TYPE_1__*,int,int,int,int*) ; 
 int /*<<< orphan*/  spinand_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wait_till_ready (TYPE_1__*) ; 

__attribute__((used)) static void spinand_cmdfunc(struct mtd_info *mtd, unsigned int command,
			    int column, int page)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct spinand_info *info = nand_get_controller_data(chip);
	struct spinand_state *state = info->priv;

	switch (command) {
	/*
	 * READ0 - read in first  0x800 bytes
	 */
	case NAND_CMD_READ1:
	case NAND_CMD_READ0:
		state->buf_ptr = 0;
		spinand_read_page(info->spi, page, 0x0, 0x840, state->buf);
		break;
	/* READOOB reads only the OOB because no ECC is performed. */
	case NAND_CMD_READOOB:
		state->buf_ptr = 0;
		spinand_read_page(info->spi, page, 0x800, 0x40, state->buf);
		break;
	case NAND_CMD_RNDOUT:
		state->buf_ptr = column;
		break;
	case NAND_CMD_READID:
		state->buf_ptr = 0;
		spinand_read_id(info->spi, state->buf);
		break;
	case NAND_CMD_PARAM:
		state->buf_ptr = 0;
		break;
	/* ERASE1 stores the block and page address */
	case NAND_CMD_ERASE1:
		spinand_erase_block(info->spi, page);
		break;
	/* ERASE2 uses the block and page address from ERASE1 */
	case NAND_CMD_ERASE2:
		break;
	/* SEQIN sets up the addr buffer and all registers except the length */
	case NAND_CMD_SEQIN:
		state->col = column;
		state->row = page;
		state->buf_ptr = 0;
		break;
	/* PAGEPROG reuses all of the setup from SEQIN and adds the length */
	case NAND_CMD_PAGEPROG:
		spinand_program_page(info->spi, state->row, state->col,
				     state->buf_ptr, state->buf);
		break;
	case NAND_CMD_STATUS:
		spinand_get_otp(info->spi, state->buf);
		if (!(state->buf[0] & 0x80))
			state->buf[0] = 0x80;
		state->buf_ptr = 0;
		break;
	/* RESET command */
	case NAND_CMD_RESET:
		if (wait_till_ready(info->spi))
			dev_err(&info->spi->dev, "WAIT timedout!!!\n");
		/* a minimum of 250us must elapse before issuing RESET cmd*/
		usleep_range(250, 1000);
		spinand_reset(info->spi);
		break;
	default:
		dev_err(&mtd->dev, "Unknown CMD: 0x%x\n", command);
	}
}