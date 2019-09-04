#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfa_ioc_s {TYPE_1__* ioc_hwif; } ;
struct TYPE_2__ {int /*<<< orphan*/  ioc_get_alt_fwstate; int /*<<< orphan*/  ioc_set_alt_fwstate; int /*<<< orphan*/  ioc_get_fwstate; int /*<<< orphan*/  ioc_set_fwstate; int /*<<< orphan*/  ioc_sync_complete; int /*<<< orphan*/  ioc_sync_ack; int /*<<< orphan*/  ioc_sync_leave; int /*<<< orphan*/  ioc_sync_join; int /*<<< orphan*/  ioc_sync_start; int /*<<< orphan*/  ioc_ownership_reset; int /*<<< orphan*/  ioc_notify_fail; int /*<<< orphan*/  ioc_isr_mode_set; int /*<<< orphan*/  ioc_map_port; int /*<<< orphan*/  ioc_reg_init; int /*<<< orphan*/  ioc_firmware_unlock; int /*<<< orphan*/  ioc_firmware_lock; int /*<<< orphan*/  ioc_pll_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_cb_firmware_lock ; 
 int /*<<< orphan*/  bfa_ioc_cb_firmware_unlock ; 
 int /*<<< orphan*/  bfa_ioc_cb_get_alt_ioc_fwstate ; 
 int /*<<< orphan*/  bfa_ioc_cb_get_cur_ioc_fwstate ; 
 int /*<<< orphan*/  bfa_ioc_cb_isr_mode_set ; 
 int /*<<< orphan*/  bfa_ioc_cb_map_port ; 
 int /*<<< orphan*/  bfa_ioc_cb_notify_fail ; 
 int /*<<< orphan*/  bfa_ioc_cb_ownership_reset ; 
 int /*<<< orphan*/  bfa_ioc_cb_pll_init ; 
 int /*<<< orphan*/  bfa_ioc_cb_reg_init ; 
 int /*<<< orphan*/  bfa_ioc_cb_set_alt_ioc_fwstate ; 
 int /*<<< orphan*/  bfa_ioc_cb_set_cur_ioc_fwstate ; 
 int /*<<< orphan*/  bfa_ioc_cb_sync_ack ; 
 int /*<<< orphan*/  bfa_ioc_cb_sync_complete ; 
 int /*<<< orphan*/  bfa_ioc_cb_sync_join ; 
 int /*<<< orphan*/  bfa_ioc_cb_sync_leave ; 
 int /*<<< orphan*/  bfa_ioc_cb_sync_start ; 
 TYPE_1__ hwif_cb ; 

void
bfa_ioc_set_cb_hwif(struct bfa_ioc_s *ioc)
{
	hwif_cb.ioc_pll_init = bfa_ioc_cb_pll_init;
	hwif_cb.ioc_firmware_lock = bfa_ioc_cb_firmware_lock;
	hwif_cb.ioc_firmware_unlock = bfa_ioc_cb_firmware_unlock;
	hwif_cb.ioc_reg_init = bfa_ioc_cb_reg_init;
	hwif_cb.ioc_map_port = bfa_ioc_cb_map_port;
	hwif_cb.ioc_isr_mode_set = bfa_ioc_cb_isr_mode_set;
	hwif_cb.ioc_notify_fail = bfa_ioc_cb_notify_fail;
	hwif_cb.ioc_ownership_reset = bfa_ioc_cb_ownership_reset;
	hwif_cb.ioc_sync_start = bfa_ioc_cb_sync_start;
	hwif_cb.ioc_sync_join = bfa_ioc_cb_sync_join;
	hwif_cb.ioc_sync_leave = bfa_ioc_cb_sync_leave;
	hwif_cb.ioc_sync_ack = bfa_ioc_cb_sync_ack;
	hwif_cb.ioc_sync_complete = bfa_ioc_cb_sync_complete;
	hwif_cb.ioc_set_fwstate = bfa_ioc_cb_set_cur_ioc_fwstate;
	hwif_cb.ioc_get_fwstate = bfa_ioc_cb_get_cur_ioc_fwstate;
	hwif_cb.ioc_set_alt_fwstate = bfa_ioc_cb_set_alt_ioc_fwstate;
	hwif_cb.ioc_get_alt_fwstate = bfa_ioc_cb_get_alt_ioc_fwstate;

	ioc->ioc_hwif = &hwif_cb;
}