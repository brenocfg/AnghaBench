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
typedef  scalar_t__ u32 ;
struct vnt_private {int /*<<< orphan*/ * ofdm_pwr_tbl; int /*<<< orphan*/ * ofdm_a_pwr_tbl; int /*<<< orphan*/ * cck_pwr_tbl; int /*<<< orphan*/  cck_pwr; } ;

/* Variables and functions */
 scalar_t__ CB_MAX_CHANNEL_24G ; 
 int EINVAL ; 
#define  RATE_11M 139 
#define  RATE_12M 138 
#define  RATE_18M 137 
#define  RATE_1M 136 
#define  RATE_24M 135 
#define  RATE_2M 134 
#define  RATE_36M 133 
#define  RATE_48M 132 
#define  RATE_54M 131 
#define  RATE_5M 130 
#define  RATE_6M 129 
#define  RATE_9M 128 
 int vnt_rf_set_txpower (struct vnt_private*,int /*<<< orphan*/ ,scalar_t__) ; 

int vnt_rf_setpower(struct vnt_private *priv, u32 rate, u32 channel)
{
	u8 power = priv->cck_pwr;

	if (channel == 0)
		return -EINVAL;

	switch (rate) {
	case RATE_1M:
	case RATE_2M:
	case RATE_5M:
	case RATE_11M:
		channel--;

		if (channel < sizeof(priv->cck_pwr_tbl))
			power = priv->cck_pwr_tbl[channel];
		break;
	case RATE_6M:
	case RATE_9M:
	case RATE_12M:
	case RATE_18M:
	case RATE_24M:
	case RATE_36M:
	case RATE_48M:
	case RATE_54M:
		if (channel > CB_MAX_CHANNEL_24G)
			power = priv->ofdm_a_pwr_tbl[channel - 15];
		else
			power = priv->ofdm_pwr_tbl[channel - 1];
		break;
	}

	return vnt_rf_set_txpower(priv, power, rate);
}