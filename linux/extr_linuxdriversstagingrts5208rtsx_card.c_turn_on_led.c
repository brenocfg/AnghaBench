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
 scalar_t__ CHECK_PID (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  rtsx_write_register (struct rtsx_chip*,int /*<<< orphan*/ ,int,int) ; 

void turn_on_led(struct rtsx_chip *chip, u8 gpio)
{
	if (CHECK_PID(chip, 0x5288))
		rtsx_write_register(chip, CARD_GPIO, (u8)(1 << gpio),
				    (u8)(1 << gpio));
	else
		rtsx_write_register(chip, CARD_GPIO, (u8)(1 << gpio), 0);
}