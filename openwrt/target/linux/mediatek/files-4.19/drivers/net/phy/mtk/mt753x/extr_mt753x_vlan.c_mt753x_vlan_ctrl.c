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
struct gsw_mt753x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTCR ; 
 int VTCR_BUSY ; 
 int VTCR_FUNC_M ; 
 int VTCR_FUNC_S ; 
 int VTCR_VID_M ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int mt753x_reg_read (struct gsw_mt753x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void mt753x_vlan_ctrl(struct gsw_mt753x *gsw, u32 cmd, u32 val)
{
	int i;

	mt753x_reg_write(gsw, VTCR,
			 VTCR_BUSY | ((cmd << VTCR_FUNC_S) & VTCR_FUNC_M) |
			 (val & VTCR_VID_M));

	for (i = 0; i < 300; i++) {
		u32 val = mt753x_reg_read(gsw, VTCR);

		if ((val & VTCR_BUSY) == 0)
			break;

		usleep_range(1000, 1100);
	}

	if (i == 300)
		dev_info(gsw->dev, "vtcr timeout\n");
}