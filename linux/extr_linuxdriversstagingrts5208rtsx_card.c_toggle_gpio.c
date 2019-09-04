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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_GPIO ; 
 int /*<<< orphan*/  rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 

void toggle_gpio(struct rtsx_chip *chip, u8 gpio)
{
	u8 temp_reg;

	rtsx_read_register(chip, CARD_GPIO, &temp_reg);
	temp_reg ^= (0x01 << gpio);
	rtsx_write_register(chip, CARD_GPIO, 0xFF, temp_reg);
}