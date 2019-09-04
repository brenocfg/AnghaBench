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
struct ipw_tgi_tx_key {int key_id; int security_type; void** tx_counter; scalar_t__ flags; scalar_t__ station_index; int /*<<< orphan*/  key; } ;
struct ipw_priv {TYPE_2__* ieee; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_3__ {int flags; int /*<<< orphan*/ * keys; } ;
struct TYPE_4__ {TYPE_1__ sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_CMD_TGI_TX_KEY ; 
 int /*<<< orphan*/  SCM_TEMPORAL_KEY_LENGTH ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_send_cmd_pdu (struct ipw_priv*,int /*<<< orphan*/ ,int,struct ipw_tgi_tx_key*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw_send_tgi_tx_key(struct ipw_priv *priv, int type, int index)
{
	struct ipw_tgi_tx_key key;

	if (!(priv->ieee->sec.flags & (1 << index)))
		return;

	key.key_id = index;
	memcpy(key.key, priv->ieee->sec.keys[index], SCM_TEMPORAL_KEY_LENGTH);
	key.security_type = type;
	key.station_index = 0;	/* always 0 for BSS */
	key.flags = 0;
	/* 0 for new key; previous value of counter (after fatal error) */
	key.tx_counter[0] = cpu_to_le32(0);
	key.tx_counter[1] = cpu_to_le32(0);

	ipw_send_cmd_pdu(priv, IPW_CMD_TGI_TX_KEY, sizeof(key), &key);
}