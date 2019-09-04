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
struct spi_device {int /*<<< orphan*/  dev; } ;
typedef  enum antenna_impedance { ____Placeholder_antenna_impedance } antenna_impedance ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MASK_LNA_ZIN ; 
 int /*<<< orphan*/  REG_LNA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
#define  fifty_ohm 129 
 int rf69_clear_bit (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rf69_set_bit (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  two_hundred_ohm 128 

int rf69_set_antenna_impedance(struct spi_device *spi,
			       enum antenna_impedance antenna_impedance)
{
	switch (antenna_impedance) {
	case fifty_ohm:
		return rf69_clear_bit(spi, REG_LNA, MASK_LNA_ZIN);
	case two_hundred_ohm:
		return rf69_set_bit(spi, REG_LNA, MASK_LNA_ZIN);
	default:
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}
}