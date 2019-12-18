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
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_2WIRE_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_2WIRE_DATA ; 
 int OXYGEN_2WIRE_DIR_WRITE ; 
 int /*<<< orphan*/  OXYGEN_2WIRE_MAP ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  oxygen_write8 (struct oxygen*,int /*<<< orphan*/ ,int) ; 

void oxygen_write_i2c(struct oxygen *chip, u8 device, u8 map, u8 data)
{
	/* should not need more than about 300 us */
	msleep(1);

	oxygen_write8(chip, OXYGEN_2WIRE_MAP, map);
	oxygen_write8(chip, OXYGEN_2WIRE_DATA, data);
	oxygen_write8(chip, OXYGEN_2WIRE_CONTROL,
		      device | OXYGEN_2WIRE_DIR_WRITE);
}