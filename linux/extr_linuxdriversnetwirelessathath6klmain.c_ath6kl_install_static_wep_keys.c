#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct ath6kl_vif {size_t def_txkey_index; TYPE_2__* wep_key_list; int /*<<< orphan*/  fw_vif_idx; TYPE_1__* ar; } ;
struct TYPE_4__ {int /*<<< orphan*/  key; scalar_t__ key_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 size_t GROUP_USAGE ; 
 int /*<<< orphan*/  KEY_OP_INIT_VAL ; 
 int /*<<< orphan*/  NO_SYNC_WMIFLAG ; 
 size_t TX_USAGE ; 
 int /*<<< orphan*/  WEP_CRYPT ; 
 size_t WMI_MAX_KEY_INDEX ; 
 int /*<<< orphan*/  ath6kl_wmi_addkey_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,size_t,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_install_static_wep_keys(struct ath6kl_vif *vif)
{
	u8 index;
	u8 keyusage;

	for (index = 0; index <= WMI_MAX_KEY_INDEX; index++) {
		if (vif->wep_key_list[index].key_len) {
			keyusage = GROUP_USAGE;
			if (index == vif->def_txkey_index)
				keyusage |= TX_USAGE;

			ath6kl_wmi_addkey_cmd(vif->ar->wmi, vif->fw_vif_idx,
					      index,
					      WEP_CRYPT,
					      keyusage,
					      vif->wep_key_list[index].key_len,
					      NULL, 0,
					      vif->wep_key_list[index].key,
					      KEY_OP_INIT_VAL, NULL,
					      NO_SYNC_WMIFLAG);
		}
	}
}