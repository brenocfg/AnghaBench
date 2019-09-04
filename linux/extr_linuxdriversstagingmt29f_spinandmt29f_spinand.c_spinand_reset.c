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
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ spinand_cmd (struct spi_device*,struct spinand_cmd*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 scalar_t__ wait_till_ready (struct spi_device*) ; 

__attribute__((used)) static void spinand_reset(struct spi_device *spi_nand)
{
	struct spinand_cmd cmd = {0};

	cmd.cmd = CMD_RESET;

	if (spinand_cmd(spi_nand, &cmd) < 0)
		pr_info("spinand reset failed!\n");

	/* elapse 1ms before issuing any other command */
	usleep_range(1000, 2000);

	if (wait_till_ready(spi_nand))
		dev_err(&spi_nand->dev, "wait timedout!\n");
}