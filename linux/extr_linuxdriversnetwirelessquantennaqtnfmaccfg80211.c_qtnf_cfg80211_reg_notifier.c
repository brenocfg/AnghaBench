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
struct wiphy {int /*<<< orphan*/ * bands; } ;
struct regulatory_request {unsigned int* alpha2; int /*<<< orphan*/  initiator; } ;
struct qtnf_wmac {int /*<<< orphan*/  macid; struct qtnf_bus* bus; } ;
struct TYPE_2__ {int mac_bitmap; } ;
struct qtnf_bus {struct qtnf_wmac** mac; TYPE_1__ hw_info; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int EALREADY ; 
 int EOPNOTSUPP ; 
 int NUM_NL80211_BANDS ; 
 unsigned int QTNF_MAX_MAC ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,int) ; 
 struct wiphy* priv_to_wiphy (struct qtnf_wmac*) ; 
 int qtnf_cmd_band_info_get (struct qtnf_wmac*,int /*<<< orphan*/ ) ; 
 int qtnf_cmd_reg_notify (struct qtnf_bus*,struct regulatory_request*) ; 
 struct qtnf_wmac* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static void qtnf_cfg80211_reg_notifier(struct wiphy *wiphy_in,
				       struct regulatory_request *req)
{
	struct qtnf_wmac *mac = wiphy_priv(wiphy_in);
	struct qtnf_bus *bus = mac->bus;
	struct wiphy *wiphy;
	unsigned int mac_idx;
	enum nl80211_band band;
	int ret;

	pr_debug("MAC%u: initiator=%d alpha=%c%c\n", mac->macid, req->initiator,
		 req->alpha2[0], req->alpha2[1]);

	ret = qtnf_cmd_reg_notify(bus, req);
	if (ret) {
		if (ret != -EOPNOTSUPP && ret != -EALREADY)
			pr_err("failed to update reg domain to %c%c\n",
			       req->alpha2[0], req->alpha2[1]);
		return;
	}

	for (mac_idx = 0; mac_idx < QTNF_MAX_MAC; ++mac_idx) {
		if (!(bus->hw_info.mac_bitmap & (1 << mac_idx)))
			continue;

		mac = bus->mac[mac_idx];
		if (!mac)
			continue;

		wiphy = priv_to_wiphy(mac);

		for (band = 0; band < NUM_NL80211_BANDS; ++band) {
			if (!wiphy->bands[band])
				continue;

			ret = qtnf_cmd_band_info_get(mac, wiphy->bands[band]);
			if (ret)
				pr_err("failed to get chan info for mac %u band %u\n",
				       mac_idx, band);
		}
	}
}