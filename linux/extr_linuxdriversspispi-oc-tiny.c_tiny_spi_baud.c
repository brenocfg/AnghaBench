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
struct tiny_spi {unsigned int baudwidth; int /*<<< orphan*/  freq; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 struct tiny_spi* tiny_spi_to_hw (struct spi_device*) ; 

__attribute__((used)) static unsigned int tiny_spi_baud(struct spi_device *spi, unsigned int hz)
{
	struct tiny_spi *hw = tiny_spi_to_hw(spi);

	return min(DIV_ROUND_UP(hw->freq, hz * 2), (1U << hw->baudwidth)) - 1;
}