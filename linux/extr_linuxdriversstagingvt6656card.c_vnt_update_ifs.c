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
typedef  int u8 ;
struct vnt_private {scalar_t__ packet_type; int slot; int rf_type; scalar_t__ eifs; void* difs; void* sifs; int /*<<< orphan*/  bb_type; scalar_t__ short_slot_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_TYPE_11A ; 
 int /*<<< orphan*/  BB_TYPE_11B ; 
 scalar_t__ C_EIFS ; 
 void* C_SIFS_A ; 
 void* C_SIFS_BG ; 
 int C_SLOT_LONG ; 
 int C_SLOT_SHORT ; 
 int /*<<< orphan*/  MAC_REG_CWMAXMIN0 ; 
 int /*<<< orphan*/  MAC_REG_SIFS ; 
 int /*<<< orphan*/  MESSAGE_REQUEST_MACREG ; 
 int /*<<< orphan*/  MESSAGE_TYPE_WRITE ; 
 scalar_t__ PK_TYPE_11A ; 
#define  RF_AIROHA7230 135 
#define  RF_AL2230 134 
#define  RF_AL2230S 133 
#define  RF_MAXIM2829 132 
#define  RF_RFMD2959 131 
#define  RF_VT3226 130 
#define  RF_VT3226D0 129 
#define  RF_VT3342A0 128 
 int /*<<< orphan*/  vnt_control_out (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

void vnt_update_ifs(struct vnt_private *priv)
{
	u8 max_min = 0;
	u8 data[4];

	if (priv->packet_type == PK_TYPE_11A) {
		priv->slot = C_SLOT_SHORT;
		priv->sifs = C_SIFS_A;
		priv->difs = C_SIFS_A + 2 * C_SLOT_SHORT;
		max_min = 4;
	} else {
		priv->sifs = C_SIFS_BG;

		if (priv->short_slot_time) {
			priv->slot = C_SLOT_SHORT;
			max_min = 4;
		} else {
			priv->slot = C_SLOT_LONG;
			max_min = 5;
		}

		priv->difs = C_SIFS_BG + 2 * priv->slot;
	}

	priv->eifs = C_EIFS;

	switch (priv->rf_type) {
	case RF_VT3226D0:
		if (priv->bb_type != BB_TYPE_11B) {
			priv->sifs -= 1;
			priv->difs -= 1;
			break;
		}
		/* fall through */
	case RF_AIROHA7230:
	case RF_AL2230:
	case RF_AL2230S:
		if (priv->bb_type != BB_TYPE_11B)
			break;
		/* fall through */
	case RF_RFMD2959:
	case RF_VT3226:
	case RF_VT3342A0:
		priv->sifs -= 3;
		priv->difs -= 3;
		break;
	case RF_MAXIM2829:
		if (priv->bb_type == BB_TYPE_11A) {
			priv->sifs -= 5;
			priv->difs -= 5;
		} else {
			priv->sifs -= 2;
			priv->difs -= 2;
		}

		break;
	}

	data[0] = (u8)priv->sifs;
	data[1] = (u8)priv->difs;
	data[2] = (u8)priv->eifs;
	data[3] = (u8)priv->slot;

	vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_SIFS,
			MESSAGE_REQUEST_MACREG, 4, &data[0]);

	max_min |= 0xa0;

	vnt_control_out(priv, MESSAGE_TYPE_WRITE, MAC_REG_CWMAXMIN0,
			MESSAGE_REQUEST_MACREG, 1, &max_min);
}