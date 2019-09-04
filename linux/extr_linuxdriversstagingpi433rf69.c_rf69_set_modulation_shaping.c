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
typedef  enum mod_shaping { ____Placeholder_mod_shaping } mod_shaping ;

/* Variables and functions */
 int /*<<< orphan*/  DATAMODUL_MODULATION_SHAPE_0_3 ; 
 int /*<<< orphan*/  DATAMODUL_MODULATION_SHAPE_0_5 ; 
 int /*<<< orphan*/  DATAMODUL_MODULATION_SHAPE_1_0 ; 
 int /*<<< orphan*/  DATAMODUL_MODULATION_SHAPE_2BR ; 
 int /*<<< orphan*/  DATAMODUL_MODULATION_SHAPE_BR ; 
 int /*<<< orphan*/  DATAMODUL_MODULATION_SHAPE_NONE ; 
 int EINVAL ; 
#define  FSK 135 
 int /*<<< orphan*/  MASK_DATAMODUL_MODULATION_SHAPE ; 
#define  OOK 134 
 int /*<<< orphan*/  REG_DATAMODUL ; 
#define  SHAPING_0_3 133 
#define  SHAPING_0_5 132 
#define  SHAPING_1_0 131 
#define  SHAPING_2BR 130 
#define  SHAPING_BR 129 
#define  SHAPING_OFF 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int rf69_get_modulation (struct spi_device*) ; 
 int rf69_read_mod_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rf69_set_modulation_shaping(struct spi_device *spi,
				enum mod_shaping mod_shaping)
{
	switch (rf69_get_modulation(spi)) {
	case FSK:
		switch (mod_shaping) {
		case SHAPING_OFF:
			return rf69_read_mod_write(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_NONE);
		case SHAPING_1_0:
			return rf69_read_mod_write(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_1_0);
		case SHAPING_0_5:
			return rf69_read_mod_write(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_0_5);
		case SHAPING_0_3:
			return rf69_read_mod_write(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_0_3);
		default:
			dev_dbg(&spi->dev, "set: illegal input param");
			return -EINVAL;
		}
	case OOK:
		switch (mod_shaping) {
		case SHAPING_OFF:
			return rf69_read_mod_write(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_NONE);
		case SHAPING_BR:
			return rf69_read_mod_write(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_BR);
		case SHAPING_2BR:
			return rf69_read_mod_write(spi, REG_DATAMODUL,
						   MASK_DATAMODUL_MODULATION_SHAPE,
						   DATAMODUL_MODULATION_SHAPE_2BR);
		default:
			dev_dbg(&spi->dev, "set: illegal input param");
			return -EINVAL;
		}
	default:
		dev_dbg(&spi->dev, "set: modulation undefined");
		return -EINVAL;
	}
}