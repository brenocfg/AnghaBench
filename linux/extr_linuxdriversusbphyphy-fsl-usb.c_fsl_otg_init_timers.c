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
struct otg_fsm {int /*<<< orphan*/  b_srp_done; int /*<<< orphan*/  b_se0_srp; int /*<<< orphan*/  b_ase0_brst_tmout; int /*<<< orphan*/  a_aidl_bdis_tmout; int /*<<< orphan*/  a_wait_bcon_tmout; int /*<<< orphan*/  a_wait_vrise_tmout; } ;

/* Variables and functions */
 int ENOMEM ; 
 int TA_AIDL_BDIS ; 
 int TA_WAIT_BCON ; 
 int TA_WAIT_VRISE ; 
 int TB_ASE0_BRST ; 
 int TB_DATA_PLS ; 
 int TB_SE0_SRP ; 
 int TB_SRP_FAIL ; 
 int TB_SRP_WAIT ; 
 int TB_VBUS_PLS ; 
 void* a_aidl_bdis_tmr ; 
 void* a_wait_bcon_tmr ; 
 int /*<<< orphan*/  a_wait_enum ; 
 void* a_wait_enum_tmr ; 
 void* a_wait_vrise_tmr ; 
 void* b_ase0_brst_tmr ; 
 int /*<<< orphan*/  b_data_pulse_end ; 
 void* b_data_pulse_tmr ; 
 void* b_se0_srp_tmr ; 
 int /*<<< orphan*/  b_srp_end ; 
 void* b_srp_fail_tmr ; 
 void* b_srp_wait_tmr ; 
 int /*<<< orphan*/  b_vbus_pulse_end ; 
 void* b_vbus_pulse_tmr ; 
 void* otg_timer_initializer (int /*<<< orphan*/ *,int,unsigned long) ; 
 int /*<<< orphan*/  set_tmout ; 

int fsl_otg_init_timers(struct otg_fsm *fsm)
{
	/* FSM used timers */
	a_wait_vrise_tmr = otg_timer_initializer(&set_tmout, TA_WAIT_VRISE,
				(unsigned long)&fsm->a_wait_vrise_tmout);
	if (!a_wait_vrise_tmr)
		return -ENOMEM;

	a_wait_bcon_tmr = otg_timer_initializer(&set_tmout, TA_WAIT_BCON,
				(unsigned long)&fsm->a_wait_bcon_tmout);
	if (!a_wait_bcon_tmr)
		return -ENOMEM;

	a_aidl_bdis_tmr = otg_timer_initializer(&set_tmout, TA_AIDL_BDIS,
				(unsigned long)&fsm->a_aidl_bdis_tmout);
	if (!a_aidl_bdis_tmr)
		return -ENOMEM;

	b_ase0_brst_tmr = otg_timer_initializer(&set_tmout, TB_ASE0_BRST,
				(unsigned long)&fsm->b_ase0_brst_tmout);
	if (!b_ase0_brst_tmr)
		return -ENOMEM;

	b_se0_srp_tmr = otg_timer_initializer(&set_tmout, TB_SE0_SRP,
				(unsigned long)&fsm->b_se0_srp);
	if (!b_se0_srp_tmr)
		return -ENOMEM;

	b_srp_fail_tmr = otg_timer_initializer(&set_tmout, TB_SRP_FAIL,
				(unsigned long)&fsm->b_srp_done);
	if (!b_srp_fail_tmr)
		return -ENOMEM;

	a_wait_enum_tmr = otg_timer_initializer(&a_wait_enum, 10,
				(unsigned long)&fsm);
	if (!a_wait_enum_tmr)
		return -ENOMEM;

	/* device driver used timers */
	b_srp_wait_tmr = otg_timer_initializer(&b_srp_end, TB_SRP_WAIT, 0);
	if (!b_srp_wait_tmr)
		return -ENOMEM;

	b_data_pulse_tmr = otg_timer_initializer(&b_data_pulse_end,
				TB_DATA_PLS, 0);
	if (!b_data_pulse_tmr)
		return -ENOMEM;

	b_vbus_pulse_tmr = otg_timer_initializer(&b_vbus_pulse_end,
				TB_VBUS_PLS, 0);
	if (!b_vbus_pulse_tmr)
		return -ENOMEM;

	return 0;
}