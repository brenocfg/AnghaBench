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
typedef  void* u8 ;
typedef  int u16 ;
struct spinand_cmd {int n_addr; void** addr; int /*<<< orphan*/  cmd; int /*<<< orphan*/  member_0; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_PROG_PAGE_EXC ; 
 int spinand_cmd (struct spi_device*,struct spinand_cmd*) ; 

__attribute__((used)) static int spinand_program_execute(struct spi_device *spi_nand, u16 page_id)
{
	struct spinand_cmd cmd = {0};
	u16 row;

	row = page_id;
	cmd.cmd = CMD_PROG_PAGE_EXC;
	cmd.n_addr = 3;
	cmd.addr[0] = (u8)((row & 0xff0000) >> 16);
	cmd.addr[1] = (u8)((row & 0xff00) >> 8);
	cmd.addr[2] = (u8)(row & 0x00ff);

	return spinand_cmd(spi_nand, &cmd);
}