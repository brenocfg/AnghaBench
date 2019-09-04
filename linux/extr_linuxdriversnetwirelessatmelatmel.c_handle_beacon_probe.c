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
typedef  int u16 ;
struct atmel_private {int preamble; int channel; scalar_t__ operating_mode; scalar_t__ station_is_associated; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_TYPE_AD_HOC ; 
 int /*<<< orphan*/  BSS_TYPE_INFRASTRUCTURE ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  LOCAL_MIB_PREAMBLE_TYPE ; 
 int LONG_PREAMBLE ; 
 int /*<<< orphan*/  Local_Mib_Type ; 
 int /*<<< orphan*/  PHY_MIB_CHANNEL_POS ; 
 int /*<<< orphan*/  Phy_Mib_Type ; 
 int SHORT_PREAMBLE ; 
 int /*<<< orphan*/  STATION_STATE_JOINNING ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  atmel_enter_state (struct atmel_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_set_mib8 (struct atmel_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  join (struct atmel_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_beacon_probe(struct atmel_private *priv, u16 capability,
				u8 channel)
{
	int rejoin = 0;
	int new = capability & WLAN_CAPABILITY_SHORT_PREAMBLE ?
		SHORT_PREAMBLE : LONG_PREAMBLE;

	if (priv->preamble != new) {
		priv->preamble = new;
		rejoin = 1;
		atmel_set_mib8(priv, Local_Mib_Type, LOCAL_MIB_PREAMBLE_TYPE, new);
	}

	if (priv->channel != channel) {
		priv->channel = channel;
		rejoin = 1;
		atmel_set_mib8(priv, Phy_Mib_Type, PHY_MIB_CHANNEL_POS, channel);
	}

	if (rejoin) {
		priv->station_is_associated = 0;
		atmel_enter_state(priv, STATION_STATE_JOINNING);

		if (priv->operating_mode == IW_MODE_INFRA)
			join(priv, BSS_TYPE_INFRASTRUCTURE);
		else
			join(priv, BSS_TYPE_AD_HOC);
	}
}