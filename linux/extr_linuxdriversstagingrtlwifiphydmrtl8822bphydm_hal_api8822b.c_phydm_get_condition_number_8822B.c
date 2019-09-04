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
typedef  int s32 ;

/* Variables and functions */
 int BIT (int) ; 
 int MASKLWORD ; 
 int bw_8822b ; 
 scalar_t__ odm_get_bb_reg (struct phy_dm_struct*,int,int) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 

s32 phydm_get_condition_number_8822B(struct phy_dm_struct *dm)
{
	s32 ret_val;

	odm_set_bb_reg(dm, 0x1988, BIT(22), 0x1);
	ret_val =
		(s32)odm_get_bb_reg(dm, 0xf84, (BIT(17) | BIT(16) | MASKLWORD));

	if (bw_8822b == 0) {
		ret_val = ret_val << (8 - 4);
		ret_val = ret_val / 234;
	} else if (bw_8822b == 1) {
		ret_val = ret_val << (7 - 4);
		ret_val = ret_val / 108;
	} else if (bw_8822b == 2) {
		ret_val = ret_val << (6 - 4);
		ret_val = ret_val / 52;
	}

	return ret_val;
}