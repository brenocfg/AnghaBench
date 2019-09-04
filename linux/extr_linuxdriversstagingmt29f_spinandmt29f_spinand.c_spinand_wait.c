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
struct spinand_info {int /*<<< orphan*/  spi; } ;
struct nand_chip {int state; } ;
struct mtd_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int FL_ERASING ; 
 int HZ ; 
 int STATUS_OIP_MASK ; 
 int STATUS_READY ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 unsigned long jiffies ; 
 struct spinand_info* nand_get_controller_data (struct nand_chip*) ; 
 int spinand_read_status (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int spinand_wait(struct mtd_info *mtd, struct nand_chip *chip)
{
	struct spinand_info *info = nand_get_controller_data(chip);

	unsigned long timeo = jiffies;
	int retval, state = chip->state;
	u8 status;

	if (state == FL_ERASING)
		timeo += (HZ * 400) / 1000;
	else
		timeo += (HZ * 20) / 1000;

	while (time_before(jiffies, timeo)) {
		retval = spinand_read_status(info->spi, &status);
		if (retval < 0) {
			dev_err(&mtd->dev,
				"error %d reading status register\n", retval);
			return retval;
		}

		if ((status & STATUS_OIP_MASK) == STATUS_READY)
			return 0;

		cond_resched();
	}
	return 0;
}