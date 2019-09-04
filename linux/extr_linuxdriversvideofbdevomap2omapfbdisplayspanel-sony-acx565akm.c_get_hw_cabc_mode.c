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
struct panel_drv_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPID_CMD_READ_CABC ; 
 int /*<<< orphan*/  acx565akm_read (struct panel_drv_data*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static unsigned get_hw_cabc_mode(struct panel_drv_data *ddata)
{
	u8 cabc_ctrl;

	acx565akm_read(ddata, MIPID_CMD_READ_CABC, &cabc_ctrl, 1);
	return cabc_ctrl & 3;
}