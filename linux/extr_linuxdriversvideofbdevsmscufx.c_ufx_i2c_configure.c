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
struct ufx_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_warn_return (int,char*) ; 
 int ufx_reg_clear_and_set_bits (struct ufx_data*,int,int,int) ; 
 int ufx_reg_write (struct ufx_data*,int,int) ; 

__attribute__((used)) static int ufx_i2c_configure(struct ufx_data *dev)
{
	int status = ufx_reg_write(dev, 0x106C, 0x00);
	check_warn_return(status, "failed to disable I2C");

	status = ufx_reg_write(dev, 0x3010, 0x00000000);
	check_warn_return(status, "failed to write 0x3010");

	/* A0h is std for any EDID, right shifted by one */
	status = ufx_reg_clear_and_set_bits(dev, 0x1004, 0x3FF,	(0xA0 >> 1));
	check_warn_return(status, "failed to set TAR bits in 0x1004");

	status = ufx_reg_write(dev, 0x106C, 0x01);
	check_warn_return(status, "failed to enable I2C");

	return 0;
}