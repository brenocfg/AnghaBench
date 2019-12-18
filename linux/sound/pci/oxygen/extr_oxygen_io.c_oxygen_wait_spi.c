#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct oxygen {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int OXYGEN_SPI_BUSY ; 
 int /*<<< orphan*/  OXYGEN_SPI_CONTROL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int oxygen_read8 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int oxygen_wait_spi(struct oxygen *chip)
{
	unsigned int count;

	/*
	 * Higher timeout to be sure: 200 us;
	 * actual transaction should not need more than 40 us.
	 */
	for (count = 50; count > 0; count--) {
		udelay(4);
		if ((oxygen_read8(chip, OXYGEN_SPI_CONTROL) &
						OXYGEN_SPI_BUSY) == 0)
			return 0;
	}
	dev_err(chip->card->dev, "oxygen: SPI wait timeout\n");
	return -EIO;
}