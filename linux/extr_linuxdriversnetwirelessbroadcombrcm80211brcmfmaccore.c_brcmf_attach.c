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
struct wiphy {int dummy; } ;
struct device {int dummy; } ;
struct cfg80211_ops {int dummy; } ;
struct brcmf_pub {TYPE_1__* config; struct brcmf_mp_device* settings; TYPE_2__* bus_if; scalar_t__ hdrlen; int /*<<< orphan*/  proto_block; int /*<<< orphan*/ * if2bss; struct wiphy* wiphy; } ;
struct brcmf_mp_device {int dummy; } ;
struct TYPE_4__ {struct brcmf_pub* drvr; } ;
struct TYPE_3__ {struct cfg80211_ops* ops; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BRCMF_BSSIDX_INVALID ; 
 int /*<<< orphan*/  BRCMF_E_PSM_WATCHDOG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TRACE ; 
 int brcmf_bus_started (struct brcmf_pub*,struct cfg80211_ops*) ; 
 struct cfg80211_ops* brcmf_cfg80211_get_ops (struct brcmf_mp_device*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_detach (struct device*) ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 int /*<<< orphan*/  brcmf_fweh_attach (struct brcmf_pub*) ; 
 int /*<<< orphan*/  brcmf_fweh_register (struct brcmf_pub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int brcmf_proto_attach (struct brcmf_pub*) ; 
 int /*<<< orphan*/  brcmf_psm_watchdog_notify ; 
 TYPE_2__* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_ops*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_wiphy_dev (struct wiphy*,struct device*) ; 
 struct wiphy* wiphy_new (struct cfg80211_ops*,int) ; 
 struct brcmf_pub* wiphy_priv (struct wiphy*) ; 

int brcmf_attach(struct device *dev, struct brcmf_mp_device *settings)
{
	struct wiphy *wiphy;
	struct cfg80211_ops *ops;
	struct brcmf_pub *drvr = NULL;
	int ret = 0;
	int i;

	brcmf_dbg(TRACE, "Enter\n");

	ops = brcmf_cfg80211_get_ops(settings);
	if (!ops)
		return -ENOMEM;

	wiphy = wiphy_new(ops, sizeof(*drvr));
	if (!wiphy)
		return -ENOMEM;

	set_wiphy_dev(wiphy, dev);
	drvr = wiphy_priv(wiphy);
	drvr->wiphy = wiphy;

	for (i = 0; i < ARRAY_SIZE(drvr->if2bss); i++)
		drvr->if2bss[i] = BRCMF_BSSIDX_INVALID;

	mutex_init(&drvr->proto_block);

	/* Link to bus module */
	drvr->hdrlen = 0;
	drvr->bus_if = dev_get_drvdata(dev);
	drvr->bus_if->drvr = drvr;
	drvr->settings = settings;

	/* Attach and link in the protocol */
	ret = brcmf_proto_attach(drvr);
	if (ret != 0) {
		brcmf_err("brcmf_prot_attach failed\n");
		goto fail;
	}

	/* Attach to events important for core code */
	brcmf_fweh_register(drvr, BRCMF_E_PSM_WATCHDOG,
			    brcmf_psm_watchdog_notify);

	/* attach firmware event handler */
	brcmf_fweh_attach(drvr);

	ret = brcmf_bus_started(drvr, ops);
	if (ret != 0) {
		brcmf_err("dongle is not responding: err=%d\n", ret);
		goto fail;
	}

	drvr->config->ops = ops;
	return 0;

fail:
	brcmf_detach(dev);
	kfree(ops);

	return ret;
}