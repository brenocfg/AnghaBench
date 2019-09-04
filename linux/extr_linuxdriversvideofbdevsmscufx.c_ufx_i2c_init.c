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
typedef  int u32 ;
struct ufx_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_warn_return (int,char*) ; 
 int ufx_reg_clear_and_set_bits (struct ufx_data*,int,int,int) ; 
 int ufx_reg_read (struct ufx_data*,int,int*) ; 
 int ufx_reg_write (struct ufx_data*,int,int) ; 

__attribute__((used)) static int ufx_i2c_init(struct ufx_data *dev)
{
	u32 tmp;

	/* disable the controller before it can be reprogrammed */
	int status = ufx_reg_write(dev, 0x106C, 0x00);
	check_warn_return(status, "failed to disable I2C");

	/* Setup the clock count registers
	 * (12+1) = 13 clks @ 2.5 MHz = 5.2 uS */
	status = ufx_reg_write(dev, 0x1018, 12);
	check_warn_return(status, "error writing 0x1018");

	/* (6+8) = 14 clks @ 2.5 MHz = 5.6 uS */
	status = ufx_reg_write(dev, 0x1014, 6);
	check_warn_return(status, "error writing 0x1014");

	status = ufx_reg_read(dev, 0x1000, &tmp);
	check_warn_return(status, "error reading 0x1000");

	/* set speed to std mode */
	tmp &= ~(0x06);
	tmp |= 0x02;

	/* 7-bit (not 10-bit) addressing */
	tmp &= ~(0x10);

	/* enable restart conditions and master mode */
	tmp |= 0x21;

	status = ufx_reg_write(dev, 0x1000, tmp);
	check_warn_return(status, "error writing 0x1000");

	/* Set normal tx using target address 0 */
	status = ufx_reg_clear_and_set_bits(dev, 0x1004, 0xC00, 0x000);
	check_warn_return(status, "error setting TX mode bits in 0x1004");

	/* Enable the controller */
	status = ufx_reg_write(dev, 0x106C, 0x01);
	check_warn_return(status, "failed to enable I2C");

	return 0;
}