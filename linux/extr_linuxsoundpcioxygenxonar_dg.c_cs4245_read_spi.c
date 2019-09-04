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
struct oxygen {struct dg* model_data; } ;
struct dg {int /*<<< orphan*/ * cs4245_shadow; } ;

/* Variables and functions */
 int CS4245_SPI_ADDRESS ; 
 int CS4245_SPI_READ ; 
 int CS4245_SPI_WRITE ; 
 int OXYGEN_SPI_CEN_LATCH_CLOCK_HI ; 
 int OXYGEN_SPI_CLOCK_1280 ; 
 int OXYGEN_SPI_CODEC_SHIFT ; 
 int /*<<< orphan*/  OXYGEN_SPI_DATA1 ; 
 int OXYGEN_SPI_DATA_LENGTH_2 ; 
 int OXYGEN_SPI_TRIGGER ; 
 int /*<<< orphan*/  oxygen_read8 (struct oxygen*,int /*<<< orphan*/ ) ; 
 int oxygen_write_spi (struct oxygen*,int,int) ; 

int cs4245_read_spi(struct oxygen *chip, u8 addr)
{
	struct dg *data = chip->model_data;
	int ret;

	ret = oxygen_write_spi(chip, OXYGEN_SPI_TRIGGER |
		OXYGEN_SPI_DATA_LENGTH_2 |
		OXYGEN_SPI_CEN_LATCH_CLOCK_HI |
		OXYGEN_SPI_CLOCK_1280 | (0 << OXYGEN_SPI_CODEC_SHIFT),
		((CS4245_SPI_ADDRESS | CS4245_SPI_WRITE) << 8) | addr);
	if (ret < 0)
		return ret;

	ret = oxygen_write_spi(chip, OXYGEN_SPI_TRIGGER |
		OXYGEN_SPI_DATA_LENGTH_2 |
		OXYGEN_SPI_CEN_LATCH_CLOCK_HI |
		OXYGEN_SPI_CLOCK_1280 | (0 << OXYGEN_SPI_CODEC_SHIFT),
		(CS4245_SPI_ADDRESS | CS4245_SPI_READ) << 8);
	if (ret < 0)
		return ret;

	data->cs4245_shadow[addr] = oxygen_read8(chip, OXYGEN_SPI_DATA1);

	return 0;
}