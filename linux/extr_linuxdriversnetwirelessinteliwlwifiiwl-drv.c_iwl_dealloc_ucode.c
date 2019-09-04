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
struct TYPE_2__ {scalar_t__ img; int /*<<< orphan*/  iml; int /*<<< orphan*/  dbg_mem_tlv; int /*<<< orphan*/ * dbg_trigger_tlv; int /*<<< orphan*/ * dbg_conf_tlv; int /*<<< orphan*/  dbg_dest_tlv; } ;
struct iwl_drv {TYPE_1__ fw; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int IWL_UCODE_TYPE_MAX ; 
 int /*<<< orphan*/  iwl_free_fw_img (struct iwl_drv*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_dealloc_ucode(struct iwl_drv *drv)
{
	int i;

	kfree(drv->fw.dbg_dest_tlv);
	for (i = 0; i < ARRAY_SIZE(drv->fw.dbg_conf_tlv); i++)
		kfree(drv->fw.dbg_conf_tlv[i]);
	for (i = 0; i < ARRAY_SIZE(drv->fw.dbg_trigger_tlv); i++)
		kfree(drv->fw.dbg_trigger_tlv[i]);
	kfree(drv->fw.dbg_mem_tlv);
	kfree(drv->fw.iml);

	for (i = 0; i < IWL_UCODE_TYPE_MAX; i++)
		iwl_free_fw_img(drv, drv->fw.img + i);
}