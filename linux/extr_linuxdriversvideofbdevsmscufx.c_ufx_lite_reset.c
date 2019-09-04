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
typedef  scalar_t__ u32 ;
struct ufx_data {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  check_warn_return (int,char*) ; 
 int ufx_reg_read (struct ufx_data*,int,scalar_t__*) ; 
 int ufx_reg_write (struct ufx_data*,int,int) ; 

__attribute__((used)) static int ufx_lite_reset(struct ufx_data *dev)
{
	int status;
	u32 value;

	status = ufx_reg_write(dev, 0x3008, 0x00000001);
	check_warn_return(status, "ufx_lite_reset error writing 0x3008");

	status = ufx_reg_read(dev, 0x3008, &value);
	check_warn_return(status, "ufx_lite_reset error reading 0x3008");

	return (value == 0) ? 0 : -EIO;
}