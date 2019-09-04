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
struct spinand_cmd {int /*<<< orphan*/  cmd; int /*<<< orphan*/  member_0; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WR_ENABLE ; 
 int spinand_cmd (struct spi_device*,struct spinand_cmd*) ; 

__attribute__((used)) static int spinand_write_enable(struct spi_device *spi_nand)
{
	struct spinand_cmd cmd = {0};

	cmd.cmd = CMD_WR_ENABLE;
	return spinand_cmd(spi_nand, &cmd);
}