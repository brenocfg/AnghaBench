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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NANO_SPI_ADDR ; 
 int /*<<< orphan*/  NANO_SPI_DATA ; 
 unsigned int NANO_SPI_WRITE ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int nano_player_spi_write(struct regmap *map,
				 unsigned int reg, unsigned int val)
{
	/* indirect register access */
	regmap_write(map, NANO_SPI_DATA, val);
	regmap_write(map, NANO_SPI_ADDR, reg | NANO_SPI_WRITE);
	return 0;
}