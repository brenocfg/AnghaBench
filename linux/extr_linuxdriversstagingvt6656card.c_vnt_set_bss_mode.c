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
struct vnt_private {scalar_t__ rf_type; scalar_t__ bb_type; int* bb_vga; int /*<<< orphan*/  packet_type; } ;

/* Variables and functions */
 scalar_t__ BB_TYPE_11A ; 
 scalar_t__ BB_TYPE_11B ; 
 scalar_t__ BB_TYPE_11G ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_BBREG ; 
 scalar_t__ RF_AIROHA7230 ; 
 int /*<<< orphan*/  vnt_control_out_u8 (struct vnt_private*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vnt_get_pkt_type (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_mac_set_bb_type (struct vnt_private*,scalar_t__) ; 
 int /*<<< orphan*/  vnt_set_rspinf (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_set_vga_gain_offset (struct vnt_private*,int) ; 
 int /*<<< orphan*/  vnt_update_ifs (struct vnt_private*) ; 

void vnt_set_bss_mode(struct vnt_private *priv)
{
	if (priv->rf_type == RF_AIROHA7230 && priv->bb_type == BB_TYPE_11A)
		vnt_mac_set_bb_type(priv, BB_TYPE_11G);
	else
		vnt_mac_set_bb_type(priv, priv->bb_type);

	priv->packet_type = vnt_get_pkt_type(priv);

	if (priv->bb_type == BB_TYPE_11A)
		vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG, 0x88, 0x03);
	else if (priv->bb_type == BB_TYPE_11B)
		vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG, 0x88, 0x02);
	else if (priv->bb_type == BB_TYPE_11G)
		vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG, 0x88, 0x08);

	vnt_update_ifs(priv);
	vnt_set_rspinf(priv, (u8)priv->bb_type);

	if (priv->bb_type == BB_TYPE_11A) {
		if (priv->rf_type == RF_AIROHA7230) {
			priv->bb_vga[0] = 0x20;

			vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG,
					   0xe7, priv->bb_vga[0]);
		}

		priv->bb_vga[2] = 0x10;
		priv->bb_vga[3] = 0x10;
	} else {
		if (priv->rf_type == RF_AIROHA7230) {
			priv->bb_vga[0] = 0x1c;

			vnt_control_out_u8(priv, MESSAGE_REQUEST_BBREG,
					   0xe7, priv->bb_vga[0]);
		}

		priv->bb_vga[2] = 0x0;
		priv->bb_vga[3] = 0x0;
	}

	vnt_set_vga_gain_offset(priv, priv->bb_vga[0]);
}