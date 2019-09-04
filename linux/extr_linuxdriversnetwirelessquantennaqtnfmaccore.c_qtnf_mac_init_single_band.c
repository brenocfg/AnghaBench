#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wiphy {TYPE_1__** bands; } ;
struct qtnf_wmac {int /*<<< orphan*/  macid; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_4__ {int band; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  qtnf_band_init_rates (TYPE_1__*) ; 
 int qtnf_cmd_band_info_get (struct qtnf_wmac*,TYPE_1__*) ; 

__attribute__((used)) static int qtnf_mac_init_single_band(struct wiphy *wiphy,
				     struct qtnf_wmac *mac,
				     enum nl80211_band band)
{
	int ret;

	wiphy->bands[band] = kzalloc(sizeof(*wiphy->bands[band]), GFP_KERNEL);
	if (!wiphy->bands[band])
		return -ENOMEM;

	wiphy->bands[band]->band = band;

	ret = qtnf_cmd_band_info_get(mac, wiphy->bands[band]);
	if (ret) {
		pr_err("MAC%u: band %u: failed to get chans info: %d\n",
		       mac->macid, band, ret);
		return ret;
	}

	qtnf_band_init_rates(wiphy->bands[band]);

	return 0;
}