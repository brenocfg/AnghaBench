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

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  scen ; 
 int /*<<< orphan*/  scl ; 
 int /*<<< orphan*/  sda ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u8 tpg110_readwrite_reg(bool write, u8 address, u8 outval)
{
	int i;
	u8 inval = 0;

	/* Assert SCEN */
	gpiod_set_value_cansleep(scen, 1);
	ndelay(150);
	/* Hammer out the address */
	for (i = 5; i >= 0; i--) {
		if (address & BIT(i))
			gpiod_set_value_cansleep(sda, 1);
		else
			gpiod_set_value_cansleep(sda, 0);
		ndelay(150);
		/* Send an SCL pulse */
		gpiod_set_value_cansleep(scl, 1);
		ndelay(160);
		gpiod_set_value_cansleep(scl, 0);
		ndelay(160);
	}

	if (write) {
		/* WRITE */
		gpiod_set_value_cansleep(sda, 0);
	} else {
		/* READ */
		gpiod_set_value_cansleep(sda, 1);
	}
	ndelay(150);
	/* Send an SCL pulse */
	gpiod_set_value_cansleep(scl, 1);
	ndelay(160);
	gpiod_set_value_cansleep(scl, 0);
	ndelay(160);

	if (!write)
		/* HiZ turn-around cycle */
		gpiod_direction_input(sda);
	ndelay(150);
	/* Send an SCL pulse */
	gpiod_set_value_cansleep(scl, 1);
	ndelay(160);
	gpiod_set_value_cansleep(scl, 0);
	ndelay(160);

	/* Hammer in/out the data */
	for (i = 7; i >= 0; i--) {
		int value;

		if (write) {
			value = !!(outval & BIT(i));
			gpiod_set_value_cansleep(sda, value);
		} else {
			value = gpiod_get_value(sda);
			if (value)
				inval |= BIT(i);
		}
		ndelay(150);
		/* Send an SCL pulse */
		gpiod_set_value_cansleep(scl, 1);
		ndelay(160);
		gpiod_set_value_cansleep(scl, 0);
		ndelay(160);
	}

	gpiod_direction_output(sda, 0);
	/* Deassert SCEN */
	gpiod_set_value_cansleep(scen, 0);
	/* Satisfies SCEN pulse width */
	udelay(1);

	return inval;
}