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

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int rb4xx_cpld_write (unsigned char*,int) ; 

__attribute__((used)) static void rb4xx_nand_write_cmd(unsigned char cmd)
{
	unsigned char data = cmd;
	int err;

	err = rb4xx_cpld_write(&data, 1);
	if (err)
		pr_err("rb4xx_nand: write cmd failed, err=%d\n", err);
}