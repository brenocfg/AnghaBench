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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int rb4xx_cpld_read (unsigned char*,int) ; 

__attribute__((used)) static unsigned char rb4xx_nand_read_byte(struct mtd_info *mtd)
{
	unsigned char data = 0;
	int err;

	err = rb4xx_cpld_read(&data, 1);
	if (err) {
		pr_err("rb4xx_nand: read data failed, err=%d\n", err);
		data = 0xff;
	}

	return data;
}