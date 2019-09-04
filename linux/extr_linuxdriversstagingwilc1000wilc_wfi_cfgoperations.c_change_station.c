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
typedef  int /*<<< orphan*/  u8 ;
struct wiphy {int dummy; } ;
struct wilc_vif {scalar_t__ iftype; } ;
struct station_parameters {int /*<<< orphan*/  sta_flags_set; int /*<<< orphan*/  sta_flags_mask; int /*<<< orphan*/ * ht_capa; int /*<<< orphan*/  supported_rates; int /*<<< orphan*/  supported_rates_len; int /*<<< orphan*/  aid; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  member_0; } ;
struct add_sta_param {int ht_supported; int /*<<< orphan*/  flags_set; int /*<<< orphan*/  flags_mask; int /*<<< orphan*/  ht_capa; int /*<<< orphan*/  rates; int /*<<< orphan*/  rates_len; int /*<<< orphan*/  aid; int /*<<< orphan*/  bssid; TYPE_1__ member_0; } ;

/* Variables and functions */
 scalar_t__ AP_MODE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ GO_MODE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int wilc_edit_station (struct wilc_vif*,struct add_sta_param*) ; 

__attribute__((used)) static int change_station(struct wiphy *wiphy, struct net_device *dev,
			  const u8 *mac, struct station_parameters *params)
{
	int ret = 0;
	struct add_sta_param sta_params = { {0} };
	struct wilc_vif *vif = netdev_priv(dev);

	if (vif->iftype == AP_MODE || vif->iftype == GO_MODE) {
		memcpy(sta_params.bssid, mac, ETH_ALEN);
		sta_params.aid = params->aid;
		sta_params.rates_len = params->supported_rates_len;
		sta_params.rates = params->supported_rates;

		if (!params->ht_capa) {
			sta_params.ht_supported = false;
		} else {
			sta_params.ht_supported = true;
			sta_params.ht_capa = *params->ht_capa;
		}

		sta_params.flags_mask = params->sta_flags_mask;
		sta_params.flags_set = params->sta_flags_set;

		ret = wilc_edit_station(vif, &sta_params);
		if (ret)
			netdev_err(dev, "Host edit station fail\n");
	}
	return ret;
}