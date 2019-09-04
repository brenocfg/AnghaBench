#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_fw_runtime {TYPE_2__* trans; } ;
struct TYPE_5__ {TYPE_1__* cfg; } ;
struct TYPE_4__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGC_IN_SAMPLE ; 
 int /*<<< orphan*/  DBGC_OUT_CTRL ; 
 scalar_t__ IWL_DEVICE_FAMILY_7000 ; 
 int /*<<< orphan*/  MON_BUFF_SAMPLE_CTL ; 
 int /*<<< orphan*/  iwl_set_bits_prph (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_write_prph (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void iwl_fw_dbg_stop_recording(struct iwl_fw_runtime *fwrt)
{
	if (fwrt->trans->cfg->device_family == IWL_DEVICE_FAMILY_7000) {
		iwl_set_bits_prph(fwrt->trans, MON_BUFF_SAMPLE_CTL, 0x100);
	} else {
		iwl_write_prph(fwrt->trans, DBGC_IN_SAMPLE, 0);
		udelay(100);
		iwl_write_prph(fwrt->trans, DBGC_OUT_CTRL, 0);
	}
}