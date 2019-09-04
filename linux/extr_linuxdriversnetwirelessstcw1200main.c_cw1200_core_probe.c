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
struct wsm_operational_mode {int disable_more_flag_usage; int /*<<< orphan*/  power_mode; } ;
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct hwbus_priv {int dummy; } ;
struct hwbus_ops {int dummy; } ;
struct device {int dummy; } ;
struct cw1200_common {int hw_refclk; char* sdd_path; int /*<<< orphan*/  firmware_ready; int /*<<< orphan*/  wsm_startup_done; int /*<<< orphan*/  hw; struct device* pdev; struct hwbus_priv* hwbus_priv; struct hwbus_ops const* hwbus_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  cw1200_free_common (struct ieee80211_hw*) ; 
 struct ieee80211_hw* cw1200_init_common (int /*<<< orphan*/  const*,int) ; 
 int cw1200_load_firmware (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_power_mode ; 
 int cw1200_refclk ; 
 int cw1200_register_bh (struct cw1200_common*) ; 
 int cw1200_register_common (struct ieee80211_hw*) ; 
 char* cw1200_sdd_path ; 
 int /*<<< orphan*/  cw1200_unregister_bh (struct cw1200_common*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wsm_set_operational_mode (struct cw1200_common*,struct wsm_operational_mode*) ; 
 int /*<<< orphan*/  wsm_use_multi_tx_conf (struct cw1200_common*,int) ; 

int cw1200_core_probe(const struct hwbus_ops *hwbus_ops,
		      struct hwbus_priv *hwbus,
		      struct device *pdev,
		      struct cw1200_common **core,
		      int ref_clk, const u8 *macaddr,
		      const char *sdd_path, bool have_5ghz)
{
	int err = -EINVAL;
	struct ieee80211_hw *dev;
	struct cw1200_common *priv;
	struct wsm_operational_mode mode = {
		.power_mode = cw1200_power_mode,
		.disable_more_flag_usage = true,
	};

	dev = cw1200_init_common(macaddr, have_5ghz);
	if (!dev)
		goto err;

	priv = dev->priv;
	priv->hw_refclk = ref_clk;
	if (cw1200_refclk)
		priv->hw_refclk = cw1200_refclk;

	priv->sdd_path = (char *)sdd_path;
	if (cw1200_sdd_path)
		priv->sdd_path = cw1200_sdd_path;

	priv->hwbus_ops = hwbus_ops;
	priv->hwbus_priv = hwbus;
	priv->pdev = pdev;
	SET_IEEE80211_DEV(priv->hw, pdev);

	/* Pass struct cw1200_common back up */
	*core = priv;

	err = cw1200_register_bh(priv);
	if (err)
		goto err1;

	err = cw1200_load_firmware(priv);
	if (err)
		goto err2;

	if (wait_event_interruptible_timeout(priv->wsm_startup_done,
					     priv->firmware_ready,
					     3*HZ) <= 0) {
		/* TODO: Need to find how to reset device
		   in QUEUE mode properly.
		*/
		pr_err("Timeout waiting on device startup\n");
		err = -ETIMEDOUT;
		goto err2;
	}

	/* Set low-power mode. */
	wsm_set_operational_mode(priv, &mode);

	/* Enable multi-TX confirmation */
	wsm_use_multi_tx_conf(priv, true);

	err = cw1200_register_common(dev);
	if (err)
		goto err2;

	return err;

err2:
	cw1200_unregister_bh(priv);
err1:
	cw1200_free_common(dev);
err:
	*core = NULL;
	return err;
}