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
 int EIO ; 
 int /*<<< orphan*/  check_warn_return (int,char*) ; 
 int ufx_reg_read (struct ufx_data*,int,int*) ; 
 int ufx_reg_write (struct ufx_data*,int,int) ; 

__attribute__((used)) static int ufx_enable(struct ufx_data *dev, bool wait)
{
	u32 dc_ctrl, dc_sts;
	int i;

	int status = ufx_reg_read(dev, 0x2004, &dc_sts);
	check_warn_return(status, "ufx_enable error reading 0x2004");

	status = ufx_reg_read(dev, 0x2000, &dc_ctrl);
	check_warn_return(status, "ufx_enable error reading 0x2000");

	/* return success if display is already enabled */
	if ((dc_sts & 0x00000001) || (dc_ctrl & 0x00000001))
		return 0;

	/* request the DC to enable the display */
	dc_ctrl |= 0x00000001;
	status = ufx_reg_write(dev, 0x2000, dc_ctrl);
	check_warn_return(status, "ufx_enable error writing 0x2000");

	/* return success immediately if we don't have to wait */
	if (!wait)
		return 0;

	for (i = 0; i < 250; i++) {
		status = ufx_reg_read(dev, 0x2004, &dc_sts);
		check_warn_return(status, "ufx_enable error reading 0x2004");

		if (dc_sts & 0x00000001)
			return 0;
	}

	/* timed out waiting for display to enable */
	return -EIO;
}