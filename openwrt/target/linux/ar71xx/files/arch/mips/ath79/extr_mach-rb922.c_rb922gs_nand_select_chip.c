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
 int /*<<< orphan*/  RB922_GPIO_NAND_NCE ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 

__attribute__((used)) static void rb922gs_nand_select_chip(int chip_no)
{
	switch (chip_no) {
	case 0:
		gpio_set_value(RB922_GPIO_NAND_NCE, 0);
		break;
	default:
		gpio_set_value(RB922_GPIO_NAND_NCE, 1);
		break;
	}
	ndelay(500);
}