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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct lbs_private {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  key; void* keylen; void* keyinfo; void* keytypeid; void* length; void* type; } ;
struct TYPE_3__ {void* size; } ;
struct cmd_key_material {TYPE_2__ param; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_KEY_MATERIAL ; 
 int CMD_ACT_SET ; 
 int TLV_TYPE_KEY_MATERIAL ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_key_material*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (struct cmd_key_material*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_set_key_material(struct lbs_private *priv,
				int key_type, int key_info,
				const u8 *key, u16 key_len)
{
	struct cmd_key_material cmd;
	int ret;

	/*
	 * Example for WPA (TKIP):
	 *
	 * cmd       5e 00
	 * size      34 00
	 * sequence  xx xx
	 * result    00 00
	 * action    01 00
	 * TLV type  00 01    key param
	 * length    00 26
	 * key type  01 00    TKIP
	 * key info  06 00    UNICAST | ENABLED
	 * key len   20 00
	 * key       32 bytes
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_ACT_SET);
	cmd.param.type = cpu_to_le16(TLV_TYPE_KEY_MATERIAL);
	cmd.param.length = cpu_to_le16(sizeof(cmd.param) - 4);
	cmd.param.keytypeid = cpu_to_le16(key_type);
	cmd.param.keyinfo = cpu_to_le16(key_info);
	cmd.param.keylen = cpu_to_le16(key_len);
	if (key && key_len)
		memcpy(cmd.param.key, key, key_len);

	ret = lbs_cmd_with_response(priv, CMD_802_11_KEY_MATERIAL, &cmd);

	return ret;
}