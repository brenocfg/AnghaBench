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
struct xonar_wm87x6 {unsigned int* wm8766_regs; } ;
struct oxygen {struct xonar_wm87x6* model_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int OXYGEN_SPI_CEN_LATCH_CLOCK_LO ; 
 int OXYGEN_SPI_CLOCK_160 ; 
 int OXYGEN_SPI_CODEC_SHIFT ; 
 int OXYGEN_SPI_DATA_LENGTH_2 ; 
 int OXYGEN_SPI_TRIGGER ; 
 unsigned int WM8766_LDA1 ; 
 unsigned int WM8766_LDA2 ; 
 unsigned int WM8766_MASTDA ; 
 unsigned int WM8766_RDA1 ; 
 unsigned int WM8766_UPDATE ; 
 int /*<<< orphan*/  oxygen_write_spi (struct oxygen*,int,unsigned int) ; 

__attribute__((used)) static void wm8766_write(struct oxygen *chip,
			 unsigned int reg, unsigned int value)
{
	struct xonar_wm87x6 *data = chip->model_data;

	oxygen_write_spi(chip, OXYGEN_SPI_TRIGGER |
			 OXYGEN_SPI_DATA_LENGTH_2 |
			 OXYGEN_SPI_CLOCK_160 |
			 (0 << OXYGEN_SPI_CODEC_SHIFT) |
			 OXYGEN_SPI_CEN_LATCH_CLOCK_LO,
			 (reg << 9) | value);
	if (reg < ARRAY_SIZE(data->wm8766_regs)) {
		if ((reg >= WM8766_LDA1 && reg <= WM8766_RDA1) ||
		    (reg >= WM8766_LDA2 && reg <= WM8766_MASTDA))
			value &= ~WM8766_UPDATE;
		data->wm8766_regs[reg] = value;
	}
}