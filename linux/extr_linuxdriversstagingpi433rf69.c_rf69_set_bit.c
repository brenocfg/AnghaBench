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
struct spi_device {int dummy; } ;

/* Variables and functions */
 int rf69_read_reg (struct spi_device*,int) ; 
 int rf69_write_reg (struct spi_device*,int,int) ; 

__attribute__((used)) static int rf69_set_bit(struct spi_device *spi, u8 reg, u8 mask)
{
	u8 tmp;

	tmp = rf69_read_reg(spi, reg);
	tmp = tmp | mask;
	return rf69_write_reg(spi, reg, tmp);
}