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
typedef  unsigned int u8 ;
struct falcon_spi_device {unsigned int const munge_address; } ;

/* Variables and functions */

__attribute__((used)) static inline u8
falcon_spi_munge_command(const struct falcon_spi_device *spi,
			 const u8 command, const unsigned int address)
{
	return command | (((address >> 8) & spi->munge_address) << 3);
}