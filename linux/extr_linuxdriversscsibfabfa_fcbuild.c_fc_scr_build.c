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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct fc_scr_s {int /*<<< orphan*/  vu_reg_func; int /*<<< orphan*/  reg_func; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_SCR ; 
 int /*<<< orphan*/  FC_FABRIC_CONTROLLER ; 
 int /*<<< orphan*/  FC_SCR_REG_FUNC_FULL ; 
 int /*<<< orphan*/  FC_VU_SCR_REG_FUNC_FABRIC_NAME_CHANGE ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_els_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct fc_scr_s*,int /*<<< orphan*/ ,int) ; 

u16
fc_scr_build(struct fchs_s *fchs, struct fc_scr_s *scr,
		u8 set_br_reg, u32 s_id, u16 ox_id)
{
	u32        d_id = bfa_hton3b(FC_FABRIC_CONTROLLER);

	fc_els_req_build(fchs, d_id, s_id, ox_id);

	memset(scr, 0, sizeof(struct fc_scr_s));
	scr->command = FC_ELS_SCR;
	scr->reg_func = FC_SCR_REG_FUNC_FULL;
	if (set_br_reg)
		scr->vu_reg_func = FC_VU_SCR_REG_FUNC_FABRIC_NAME_CHANGE;

	return sizeof(struct fc_scr_s);
}