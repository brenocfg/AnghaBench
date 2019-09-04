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
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MASK_PALEVEL_OUTPUT_POWER ; 
 int /*<<< orphan*/  REG_PALEVEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int rf69_read_mod_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int rf69_set_output_power_level(struct spi_device *spi, u8 power_level)
{
	// TODO: Dependency to PA0,1,2 setting
	power_level += 18;

	// check input value
	if (power_level > 0x1f) {
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}

	// write value
	return rf69_read_mod_write(spi, REG_PALEVEL, MASK_PALEVEL_OUTPUT_POWER,
				   power_level);
}