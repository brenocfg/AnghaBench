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
typedef  int u32 ;
struct vnt_private {int dummy; } ;

/* Variables and functions */
 int CB_MAX_CHANNEL ; 
 int /*<<< orphan*/  MACCR_CLRNAV ; 
 int /*<<< orphan*/  MAC_REG_CHANNEL ; 
 int /*<<< orphan*/  MAC_REG_MACCR ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_SELECT_CHANNEL ; 
 int /*<<< orphan*/  vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnt_control_out_u8 (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_mac_reg_bits_off (struct vnt_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnt_mac_reg_bits_on (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vnt_set_channel(struct vnt_private *priv, u32 connection_channel)
{
	if (connection_channel > CB_MAX_CHANNEL || !connection_channel)
		return;

	/* clear NAV */
	vnt_mac_reg_bits_on(priv, MAC_REG_MACCR, MACCR_CLRNAV);

	/* Set Channel[7] = 0 to tell H/W channel is changing now. */
	vnt_mac_reg_bits_off(priv, MAC_REG_CHANNEL, 0xb0);

	vnt_control_out(priv, MESSAGE_TYPE_SELECT_CHANNEL,
			connection_channel, 0, 0, NULL);

	vnt_control_out_u8(priv, MESSAGE_REQUEST_MACREG, MAC_REG_CHANNEL,
			   (u8)(connection_channel | 0x80));
}