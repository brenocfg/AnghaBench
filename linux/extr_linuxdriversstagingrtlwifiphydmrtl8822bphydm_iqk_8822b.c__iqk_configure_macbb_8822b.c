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
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 
 int /*<<< orphan*/  odm_write_1byte (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  odm_write_4byte (struct phy_dm_struct*,int,int) ; 

__attribute__((used)) static void _iqk_configure_macbb_8822b(struct phy_dm_struct *dm)
{
	/*MACBB register setting*/
	odm_write_1byte(dm, 0x522, 0x7f);
	odm_set_bb_reg(dm, 0x550, BIT(11) | BIT(3), 0x0);
	odm_set_bb_reg(dm, 0x90c, BIT(15),
		       0x1); /*0x90c[15]=1: dac_buf reset selection*/
	odm_set_bb_reg(dm, 0x9a4, BIT(31),
		       0x0); /*0x9a4[31]=0: Select da clock*/
	/*0xc94[0]=1, 0xe94[0]=1: let tx through iqk*/
	odm_set_bb_reg(dm, 0xc94, BIT(0), 0x1);
	odm_set_bb_reg(dm, 0xe94, BIT(0), 0x1);
	/* 3-wire off*/
	odm_write_4byte(dm, 0xc00, 0x00000004);
	odm_write_4byte(dm, 0xe00, 0x00000004);
}