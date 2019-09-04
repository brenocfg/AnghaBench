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
struct bfa_ioc_s {int dummy; } ;
struct bfa_ioc_hwif_s {int /*<<< orphan*/  ioc_get_alt_fwstate; int /*<<< orphan*/  ioc_set_alt_fwstate; int /*<<< orphan*/  ioc_get_fwstate; int /*<<< orphan*/  ioc_set_fwstate; int /*<<< orphan*/  ioc_sync_complete; int /*<<< orphan*/  ioc_sync_ack; int /*<<< orphan*/  ioc_sync_leave; int /*<<< orphan*/  ioc_sync_join; int /*<<< orphan*/  ioc_sync_start; int /*<<< orphan*/  ioc_ownership_reset; int /*<<< orphan*/  ioc_notify_fail; int /*<<< orphan*/  ioc_firmware_unlock; int /*<<< orphan*/  ioc_firmware_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_ct_firmware_lock ; 
 int /*<<< orphan*/  bfa_ioc_ct_firmware_unlock ; 
 int /*<<< orphan*/  bfa_ioc_ct_get_alt_ioc_fwstate ; 
 int /*<<< orphan*/  bfa_ioc_ct_get_cur_ioc_fwstate ; 
 int /*<<< orphan*/  bfa_ioc_ct_notify_fail ; 
 int /*<<< orphan*/  bfa_ioc_ct_ownership_reset ; 
 int /*<<< orphan*/  bfa_ioc_ct_set_alt_ioc_fwstate ; 
 int /*<<< orphan*/  bfa_ioc_ct_set_cur_ioc_fwstate ; 
 int /*<<< orphan*/  bfa_ioc_ct_sync_ack ; 
 int /*<<< orphan*/  bfa_ioc_ct_sync_complete ; 
 int /*<<< orphan*/  bfa_ioc_ct_sync_join ; 
 int /*<<< orphan*/  bfa_ioc_ct_sync_leave ; 
 int /*<<< orphan*/  bfa_ioc_ct_sync_start ; 

__attribute__((used)) static void
bfa_ioc_set_ctx_hwif(struct bfa_ioc_s *ioc, struct bfa_ioc_hwif_s *hwif)
{
	hwif->ioc_firmware_lock = bfa_ioc_ct_firmware_lock;
	hwif->ioc_firmware_unlock = bfa_ioc_ct_firmware_unlock;
	hwif->ioc_notify_fail = bfa_ioc_ct_notify_fail;
	hwif->ioc_ownership_reset = bfa_ioc_ct_ownership_reset;
	hwif->ioc_sync_start = bfa_ioc_ct_sync_start;
	hwif->ioc_sync_join = bfa_ioc_ct_sync_join;
	hwif->ioc_sync_leave = bfa_ioc_ct_sync_leave;
	hwif->ioc_sync_ack = bfa_ioc_ct_sync_ack;
	hwif->ioc_sync_complete = bfa_ioc_ct_sync_complete;
	hwif->ioc_set_fwstate = bfa_ioc_ct_set_cur_ioc_fwstate;
	hwif->ioc_get_fwstate = bfa_ioc_ct_get_cur_ioc_fwstate;
	hwif->ioc_set_alt_fwstate = bfa_ioc_ct_set_alt_ioc_fwstate;
	hwif->ioc_get_alt_fwstate = bfa_ioc_ct_get_alt_ioc_fwstate;
}