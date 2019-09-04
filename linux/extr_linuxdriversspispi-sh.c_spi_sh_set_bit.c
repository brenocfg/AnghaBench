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
struct spi_sh_data {int dummy; } ;

/* Variables and functions */
 unsigned long spi_sh_read (struct spi_sh_data*,unsigned long) ; 
 int /*<<< orphan*/  spi_sh_write (struct spi_sh_data*,unsigned long,unsigned long) ; 

__attribute__((used)) static void spi_sh_set_bit(struct spi_sh_data *ss, unsigned long val,
				unsigned long offset)
{
	unsigned long tmp;

	tmp = spi_sh_read(ss, offset);
	tmp |= val;
	spi_sh_write(ss, tmp, offset);
}