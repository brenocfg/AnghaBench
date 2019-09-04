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
typedef  int u16 ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int STATUS_E_FAIL ; 
 int STATUS_E_FAIL_MASK ; 
 int STATUS_OIP_MASK ; 
 int STATUS_READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int spinand_erase_block_erase (struct spi_device*,int) ; 
 int spinand_read_status (struct spi_device*,int*) ; 
 int spinand_write_enable (struct spi_device*) ; 
 scalar_t__ wait_till_ready (struct spi_device*) ; 

__attribute__((used)) static int spinand_erase_block(struct spi_device *spi_nand, u16 block_id)
{
	int retval;
	u8 status = 0;

	retval = spinand_write_enable(spi_nand);
	if (wait_till_ready(spi_nand))
		dev_err(&spi_nand->dev, "wait timedout!!!\n");

	retval = spinand_erase_block_erase(spi_nand, block_id);
	while (1) {
		retval = spinand_read_status(spi_nand, &status);
		if (retval < 0) {
			dev_err(&spi_nand->dev,
				"error %d reading status register\n", retval);
			return retval;
		}

		if ((status & STATUS_OIP_MASK) == STATUS_READY) {
			if ((status & STATUS_E_FAIL_MASK) == STATUS_E_FAIL) {
				dev_err(&spi_nand->dev,
					"erase error, block %d\n", block_id);
				return -1;
			}
			break;
		}
	}
	return 0;
}