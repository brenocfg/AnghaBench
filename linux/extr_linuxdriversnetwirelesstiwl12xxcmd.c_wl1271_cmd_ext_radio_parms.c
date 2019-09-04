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
struct wl12xx_conf_rf {int /*<<< orphan*/  tx_per_channel_power_compensation_5; int /*<<< orphan*/  tx_per_channel_power_compensation_2; } ;
struct TYPE_4__ {struct wl12xx_conf_rf rf; } ;
struct wl12xx_priv {TYPE_2__ conf; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct wl1271_ext_radio_parms_cmd {int /*<<< orphan*/  tx_per_channel_power_compensation_5; int /*<<< orphan*/  tx_per_channel_power_compensation_2; TYPE_1__ test; } ;
struct wl1271 {int /*<<< orphan*/  nvs; struct wl12xx_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONF_TX_PWR_COMPENSATION_LEN_2 ; 
 int /*<<< orphan*/  CONF_TX_PWR_COMPENSATION_LEN_5 ; 
 int /*<<< orphan*/  DEBUG_CMD ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TEST_CMD_INI_FILE_RF_EXTENDED_PARAM ; 
 int /*<<< orphan*/  kfree (struct wl1271_ext_radio_parms_cmd*) ; 
 struct wl1271_ext_radio_parms_cmd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wl1271_cmd_test (struct wl1271*,struct wl1271_ext_radio_parms_cmd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_dump (int /*<<< orphan*/ ,char*,struct wl1271_ext_radio_parms_cmd*,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

int wl1271_cmd_ext_radio_parms(struct wl1271 *wl)
{
	struct wl1271_ext_radio_parms_cmd *ext_radio_parms;
	struct wl12xx_priv *priv = wl->priv;
	struct wl12xx_conf_rf *rf = &priv->conf.rf;
	int ret;

	if (!wl->nvs)
		return -ENODEV;

	ext_radio_parms = kzalloc(sizeof(*ext_radio_parms), GFP_KERNEL);
	if (!ext_radio_parms)
		return -ENOMEM;

	ext_radio_parms->test.id = TEST_CMD_INI_FILE_RF_EXTENDED_PARAM;

	memcpy(ext_radio_parms->tx_per_channel_power_compensation_2,
	       rf->tx_per_channel_power_compensation_2,
	       CONF_TX_PWR_COMPENSATION_LEN_2);
	memcpy(ext_radio_parms->tx_per_channel_power_compensation_5,
	       rf->tx_per_channel_power_compensation_5,
	       CONF_TX_PWR_COMPENSATION_LEN_5);

	wl1271_dump(DEBUG_CMD, "TEST_CMD_INI_FILE_EXT_RADIO_PARAM: ",
		    ext_radio_parms, sizeof(*ext_radio_parms));

	ret = wl1271_cmd_test(wl, ext_radio_parms, sizeof(*ext_radio_parms), 0);
	if (ret < 0)
		wl1271_warning("TEST_CMD_INI_FILE_RF_EXTENDED_PARAM failed");

	kfree(ext_radio_parms);
	return ret;
}