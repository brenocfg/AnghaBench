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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u16 ;
struct mwifiex_private {int dummy; } ;
struct mwifiex_ds_read_eeprom {void* byte_count; int /*<<< orphan*/  value; void* offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  HostCmd_ACT_GEN_GET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_EEPROM_ACCESS ; 
 scalar_t__ MAX_EEPROM_DATA ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (void*,void*) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_ds_read_eeprom*,int) ; 

int
mwifiex_eeprom_read(struct mwifiex_private *priv, u16 offset, u16 bytes,
		    u8 *value)
{
	int ret;
	struct mwifiex_ds_read_eeprom rd_eeprom;

	rd_eeprom.offset =  offset;
	rd_eeprom.byte_count = bytes;

	/* Send request to firmware */
	ret = mwifiex_send_cmd(priv, HostCmd_CMD_802_11_EEPROM_ACCESS,
			       HostCmd_ACT_GEN_GET, 0, &rd_eeprom, true);

	if (!ret)
		memcpy(value, rd_eeprom.value, min((u16)MAX_EEPROM_DATA,
		       rd_eeprom.byte_count));
	return ret;
}