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
struct iwl_mvm {TYPE_1__* fw; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_CDB_SUPPORT ; 
 int fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool iwl_mvm_is_cdb_supported(struct iwl_mvm *mvm)
{
	/*
	 * TODO:
	 * The issue of how to determine CDB APIs and usage is still not fully
	 * defined.
	 * There is a compilation for CDB and non-CDB FW, but there may
	 * be also runtime check.
	 * For now there is a TLV for checking compilation mode, but a
	 * runtime check will also have to be here - once defined.
	 */
	return fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_CDB_SUPPORT);
}