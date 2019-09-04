#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct adm8211_priv* priv; } ;
struct adm8211_priv {int /*<<< orphan*/  mode; TYPE_1__* pdev; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int) ; 
 int ADM8211_IER_AIE ; 
 int ADM8211_IER_GPTIE ; 
 int ADM8211_IER_NIE ; 
 int ADM8211_IER_RCIE ; 
 int ADM8211_IER_TCIE ; 
 int ADM8211_IER_TDUIE ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  RDR ; 
 int /*<<< orphan*/  adm8211_hw_init (struct ieee80211_hw*) ; 
 int adm8211_hw_reset (struct ieee80211_hw*) ; 
 int adm8211_init_rings (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  adm8211_interrupt ; 
 int /*<<< orphan*/  adm8211_rf_set_channel (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm8211_set_interval (struct ieee80211_hw*,int,int) ; 
 int /*<<< orphan*/  adm8211_update_mode (struct ieee80211_hw*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int adm8211_start(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;
	int retval;

	/* Power up MAC and RF chips */
	retval = adm8211_hw_reset(dev);
	if (retval) {
		wiphy_err(dev->wiphy, "hardware reset failed\n");
		goto fail;
	}

	retval = adm8211_init_rings(dev);
	if (retval) {
		wiphy_err(dev->wiphy, "failed to initialize rings\n");
		goto fail;
	}

	/* Init hardware */
	adm8211_hw_init(dev);
	adm8211_rf_set_channel(dev, priv->channel);

	retval = request_irq(priv->pdev->irq, adm8211_interrupt,
			     IRQF_SHARED, "adm8211", dev);
	if (retval) {
		wiphy_err(dev->wiphy, "failed to register IRQ handler\n");
		goto fail;
	}

	ADM8211_CSR_WRITE(IER, ADM8211_IER_NIE | ADM8211_IER_AIE |
			       ADM8211_IER_RCIE | ADM8211_IER_TCIE |
			       ADM8211_IER_TDUIE | ADM8211_IER_GPTIE);
	priv->mode = NL80211_IFTYPE_MONITOR;
	adm8211_update_mode(dev);
	ADM8211_CSR_WRITE(RDR, 0);

	adm8211_set_interval(dev, 100, 10);
	return 0;

fail:
	return retval;
}