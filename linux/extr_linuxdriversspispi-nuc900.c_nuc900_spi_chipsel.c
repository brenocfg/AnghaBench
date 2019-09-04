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
struct spi_device {int dummy; } ;

/* Variables and functions */
#define  BITBANG_CS_ACTIVE 129 
#define  BITBANG_CS_INACTIVE 128 
 int /*<<< orphan*/  nuc900_slave_select (struct spi_device*,int) ; 

__attribute__((used)) static void nuc900_spi_chipsel(struct spi_device *spi, int value)
{
	switch (value) {
	case BITBANG_CS_INACTIVE:
		nuc900_slave_select(spi, 0);
		break;

	case BITBANG_CS_ACTIVE:
		nuc900_slave_select(spi, 1);
		break;
	}
}