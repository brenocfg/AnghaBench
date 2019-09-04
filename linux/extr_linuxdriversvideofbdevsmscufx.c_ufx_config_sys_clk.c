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
 int /*<<< orphan*/  msleep (int) ; 
 int ufx_reg_clear_bits (struct ufx_data*,int,int) ; 
 int ufx_reg_write (struct ufx_data*,int,int) ; 

__attribute__((used)) static int ufx_config_sys_clk(struct ufx_data *dev)
{
	int status = ufx_reg_write(dev, 0x700C, 0x8000000F);
	check_warn_return(status, "error writing 0x700C");

	status = ufx_reg_write(dev, 0x7014, 0x0010024F);
	check_warn_return(status, "error writing 0x7014");

	status = ufx_reg_write(dev, 0x7010, 0x00000000);
	check_warn_return(status, "error writing 0x7010");

	status = ufx_reg_clear_bits(dev, 0x700C, 0x0000000A);
	check_warn_return(status, "error clearing PLL1 bypass in 0x700C");
	msleep(1);

	status = ufx_reg_clear_bits(dev, 0x700C, 0x80000000);
	check_warn_return(status, "error clearing output gate in 0x700C");

	return 0;
}