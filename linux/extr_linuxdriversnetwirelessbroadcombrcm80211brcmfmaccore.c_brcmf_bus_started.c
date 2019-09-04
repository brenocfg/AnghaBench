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
struct cfg80211_ops {int dummy; } ;
struct brcmf_pub {TYPE_1__* settings; struct brcmf_if** iflist; int /*<<< orphan*/ * config; struct brcmf_bus* bus_if; } ;
struct brcmf_if {int /*<<< orphan*/  ndev; } ;
struct brcmf_bus {int dummy; } ;
struct TYPE_2__ {scalar_t__ ignore_probe_fail; scalar_t__ p2p_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_BUS_UP ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct brcmf_if*) ; 
 int PTR_ERR (struct brcmf_if*) ; 
 int /*<<< orphan*/  TRACE ; 
 struct brcmf_if* brcmf_add_if (struct brcmf_pub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_bus_change_state (struct brcmf_bus*,int /*<<< orphan*/ ) ; 
 int brcmf_bus_preinit (struct brcmf_bus*) ; 
 int brcmf_c_preinit_dcmds (struct brcmf_if*) ; 
 int /*<<< orphan*/ * brcmf_cfg80211_attach (struct brcmf_pub*,struct cfg80211_ops*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_cfg80211_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_debugfs_add_entry (struct brcmf_pub*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int /*<<< orphan*/  brcmf_feat_attach (struct brcmf_pub*) ; 
 int /*<<< orphan*/  brcmf_feat_debugfs_create (struct brcmf_pub*) ; 
 int brcmf_net_attach (struct brcmf_if*,int) ; 
 int /*<<< orphan*/  brcmf_net_detach (int /*<<< orphan*/ ,int) ; 
 int brcmf_net_p2p_attach (struct brcmf_if*) ; 
 int /*<<< orphan*/  brcmf_proto_add_if (struct brcmf_pub*,struct brcmf_if*) ; 
 int /*<<< orphan*/  brcmf_proto_debugfs_create (struct brcmf_pub*) ; 
 int brcmf_proto_init_done (struct brcmf_pub*) ; 
 int /*<<< orphan*/  brcmf_revinfo_read ; 

__attribute__((used)) static int brcmf_bus_started(struct brcmf_pub *drvr, struct cfg80211_ops *ops)
{
	int ret = -1;
	struct brcmf_bus *bus_if = drvr->bus_if;
	struct brcmf_if *ifp;
	struct brcmf_if *p2p_ifp;

	brcmf_dbg(TRACE, "\n");

	/* add primary networking interface */
	ifp = brcmf_add_if(drvr, 0, 0, false, "wlan%d", NULL);
	if (IS_ERR(ifp))
		return PTR_ERR(ifp);

	p2p_ifp = NULL;

	/* signal bus ready */
	brcmf_bus_change_state(bus_if, BRCMF_BUS_UP);

	/* do bus specific preinit here */
	ret = brcmf_bus_preinit(bus_if);
	if (ret < 0)
		goto fail;

	/* Bus is ready, do any initialization */
	ret = brcmf_c_preinit_dcmds(ifp);
	if (ret < 0)
		goto fail;

	brcmf_feat_attach(drvr);

	ret = brcmf_proto_init_done(drvr);
	if (ret < 0)
		goto fail;

	brcmf_proto_add_if(drvr, ifp);

	drvr->config = brcmf_cfg80211_attach(drvr, ops,
					     drvr->settings->p2p_enable);
	if (drvr->config == NULL) {
		ret = -ENOMEM;
		goto fail;
	}

	ret = brcmf_net_attach(ifp, false);

	if ((!ret) && (drvr->settings->p2p_enable)) {
		p2p_ifp = drvr->iflist[1];
		if (p2p_ifp)
			ret = brcmf_net_p2p_attach(p2p_ifp);
	}

	if (ret)
		goto fail;

#ifdef CONFIG_INET
	drvr->inetaddr_notifier.notifier_call = brcmf_inetaddr_changed;
	ret = register_inetaddr_notifier(&drvr->inetaddr_notifier);
	if (ret)
		goto fail;

#if IS_ENABLED(CONFIG_IPV6)
	drvr->inet6addr_notifier.notifier_call = brcmf_inet6addr_changed;
	ret = register_inet6addr_notifier(&drvr->inet6addr_notifier);
	if (ret) {
		unregister_inetaddr_notifier(&drvr->inetaddr_notifier);
		goto fail;
	}
#endif
#endif /* CONFIG_INET */

	/* populate debugfs */
	brcmf_debugfs_add_entry(drvr, "revinfo", brcmf_revinfo_read);
	brcmf_feat_debugfs_create(drvr);
	brcmf_proto_debugfs_create(drvr);

	return 0;

fail:
	brcmf_err("failed: %d\n", ret);
	if (drvr->config) {
		brcmf_cfg80211_detach(drvr->config);
		drvr->config = NULL;
	}
	brcmf_net_detach(ifp->ndev, false);
	if (p2p_ifp)
		brcmf_net_detach(p2p_ifp->ndev, false);
	drvr->iflist[0] = NULL;
	drvr->iflist[1] = NULL;
	if (drvr->settings->ignore_probe_fail)
		ret = 0;

	return ret;
}