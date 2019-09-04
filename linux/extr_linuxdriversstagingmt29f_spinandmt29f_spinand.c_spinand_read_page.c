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
typedef  int /*<<< orphan*/  u16 ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int STATUS_ECC_ERROR ; 
 int STATUS_ECC_MASK ; 
 int STATUS_OIP_MASK ; 
 int STATUS_READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int spinand_read_from_cache (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int spinand_read_page_to_cache (struct spi_device*,int /*<<< orphan*/ ) ; 
 int spinand_read_status (struct spi_device*,int*) ; 
 scalar_t__ wait_till_ready (struct spi_device*) ; 

__attribute__((used)) static int spinand_read_page(struct spi_device *spi_nand, u16 page_id,
			     u16 offset, u16 len, u8 *rbuf)
{
	int ret;
	u8 status = 0;

#ifdef CONFIG_MTD_SPINAND_ONDIEECC
	if (enable_read_hw_ecc) {
		if (spinand_enable_ecc(spi_nand) < 0)
			dev_err(&spi_nand->dev, "enable HW ECC failed!");
	}
#endif
	ret = spinand_read_page_to_cache(spi_nand, page_id);
	if (ret < 0)
		return ret;

	if (wait_till_ready(spi_nand))
		dev_err(&spi_nand->dev, "WAIT timedout!!!\n");

	while (1) {
		ret = spinand_read_status(spi_nand, &status);
		if (ret < 0) {
			dev_err(&spi_nand->dev,
				"err %d read status register\n", ret);
			return ret;
		}

		if ((status & STATUS_OIP_MASK) == STATUS_READY) {
			if ((status & STATUS_ECC_MASK) == STATUS_ECC_ERROR) {
				dev_err(&spi_nand->dev, "ecc error, page=%d\n",
					page_id);
				return 0;
			}
			break;
		}
	}

	ret = spinand_read_from_cache(spi_nand, page_id, offset, len, rbuf);
	if (ret < 0) {
		dev_err(&spi_nand->dev, "read from cache failed!!\n");
		return ret;
	}

#ifdef CONFIG_MTD_SPINAND_ONDIEECC
	if (enable_read_hw_ecc) {
		ret = spinand_disable_ecc(spi_nand);
		if (ret < 0) {
			dev_err(&spi_nand->dev, "disable ecc failed!!\n");
			return ret;
		}
		enable_read_hw_ecc = 0;
	}
#endif
	return ret;
}