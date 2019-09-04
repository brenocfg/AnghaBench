#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct il_priv {int /*<<< orphan*/  sta_lock; TYPE_2__* stations; } ;
struct il_hw_key {int dummy; } ;
struct il_addsta_cmd {int dummy; } ;
struct il4965_keyinfo {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  modify_mask; } ;
struct TYPE_7__ {int /*<<< orphan*/  key_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  mode; TYPE_1__ sta; TYPE_3__ key; } ;
struct TYPE_6__ {TYPE_4__ sta; TYPE_3__ keyinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  STA_CONTROL_MODIFY_MSK ; 
 int /*<<< orphan*/  STA_KEY_FLG_NO_ENC ; 
 int /*<<< orphan*/  STA_MODIFY_KEY_MASK ; 
 int il_send_add_sta (struct il_priv*,struct il_addsta_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct il_addsta_cmd*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
il3945_clear_sta_key_info(struct il_priv *il, u8 sta_id)
{
	unsigned long flags;
	struct il_addsta_cmd sta_cmd;

	spin_lock_irqsave(&il->sta_lock, flags);
	memset(&il->stations[sta_id].keyinfo, 0, sizeof(struct il_hw_key));
	memset(&il->stations[sta_id].sta.key, 0, sizeof(struct il4965_keyinfo));
	il->stations[sta_id].sta.key.key_flags = STA_KEY_FLG_NO_ENC;
	il->stations[sta_id].sta.sta.modify_mask = STA_MODIFY_KEY_MASK;
	il->stations[sta_id].sta.mode = STA_CONTROL_MODIFY_MSK;
	memcpy(&sta_cmd, &il->stations[sta_id].sta,
	       sizeof(struct il_addsta_cmd));
	spin_unlock_irqrestore(&il->sta_lock, flags);

	D_INFO("hwcrypto: clear ucode station key info\n");
	return il_send_add_sta(il, &sta_cmd, CMD_SYNC);
}