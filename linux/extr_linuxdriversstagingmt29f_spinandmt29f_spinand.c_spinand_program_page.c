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
 int STATUS_OIP_MASK ; 
 int STATUS_P_FAIL ; 
 int STATUS_P_FAIL_MASK ; 
 int STATUS_READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int spinand_program_data_to_cache (struct spi_device*,int,int,int,int*) ; 
 int spinand_program_execute (struct spi_device*,int) ; 
 int spinand_read_status (struct spi_device*,int*) ; 
 int spinand_write_enable (struct spi_device*) ; 
 scalar_t__ wait_till_ready (struct spi_device*) ; 

__attribute__((used)) static int spinand_program_page(struct spi_device *spi_nand,
				u16 page_id, u16 offset, u16 len, u8 *buf)
{
	int retval;
	u8 status = 0;
	u8 *wbuf;
#ifdef CONFIG_MTD_SPINAND_ONDIEECC
	unsigned int i, j;

	wbuf = devm_kzalloc(&spi_nand->dev, CACHE_BUF, GFP_KERNEL);
	if (!wbuf)
		return -ENOMEM;

	enable_read_hw_ecc = 1;
	retval = spinand_read_page(spi_nand, page_id, 0, CACHE_BUF, wbuf);
	if (retval < 0) {
		dev_err(&spi_nand->dev, "ecc error on read page!!!\n");
		return retval;
	}

	for (i = offset, j = 0; i < len; i++, j++)
		wbuf[i] &= buf[j];

	if (enable_hw_ecc) {
		retval = spinand_enable_ecc(spi_nand);
		if (retval < 0) {
			dev_err(&spi_nand->dev, "enable ecc failed!!\n");
			return retval;
		}
	}
#else
	wbuf = buf;
#endif
	retval = spinand_write_enable(spi_nand);
	if (retval < 0) {
		dev_err(&spi_nand->dev, "write enable failed!!\n");
		return retval;
	}
	if (wait_till_ready(spi_nand))
		dev_err(&spi_nand->dev, "wait timedout!!!\n");

	retval = spinand_program_data_to_cache(spi_nand, page_id,
					       offset, len, wbuf);
	if (retval < 0)
		return retval;
	retval = spinand_program_execute(spi_nand, page_id);
	if (retval < 0)
		return retval;
	while (1) {
		retval = spinand_read_status(spi_nand, &status);
		if (retval < 0) {
			dev_err(&spi_nand->dev,
				"error %d reading status register\n", retval);
			return retval;
		}

		if ((status & STATUS_OIP_MASK) == STATUS_READY) {
			if ((status & STATUS_P_FAIL_MASK) == STATUS_P_FAIL) {
				dev_err(&spi_nand->dev,
					"program error, page %d\n", page_id);
				return -1;
			}
			break;
		}
	}
#ifdef CONFIG_MTD_SPINAND_ONDIEECC
	if (enable_hw_ecc) {
		retval = spinand_disable_ecc(spi_nand);
		if (retval < 0) {
			dev_err(&spi_nand->dev, "disable ecc failed!!\n");
			return retval;
		}
		enable_hw_ecc = 0;
	}
#endif

	return 0;
}