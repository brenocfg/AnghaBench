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
typedef  int /*<<< orphan*/  u8 ;
struct spinand_cmd {int n_addr; int n_tx; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/ * addr; int /*<<< orphan*/  cmd; int /*<<< orphan*/  member_0; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WRITE_REG ; 
 int /*<<< orphan*/  REG_BLOCK_LOCK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spinand_cmd (struct spi_device*,struct spinand_cmd*) ; 
 int spinand_get_otp (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spinand_lock_block(struct spi_device *spi_nand, u8 lock)
{
	struct spinand_cmd cmd = {0};
	int ret;
	u8 otp = 0;

	ret = spinand_get_otp(spi_nand, &otp);

	cmd.cmd = CMD_WRITE_REG;
	cmd.n_addr = 1;
	cmd.addr[0] = REG_BLOCK_LOCK;
	cmd.n_tx = 1;
	cmd.tx_buf = &lock;

	ret = spinand_cmd(spi_nand, &cmd);
	if (ret < 0)
		dev_err(&spi_nand->dev, "error %d lock block\n", ret);

	return ret;
}