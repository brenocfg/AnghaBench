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
struct wl12xx_rx_filter {int dummy; } ;
struct wl1271 {int dummy; } ;
struct cfg80211_wowlan {int n_patterns; struct cfg80211_pkt_pattern* patterns; scalar_t__ any; } ;
struct cfg80211_pkt_pattern {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FILTER_DROP ; 
 int /*<<< orphan*/  FILTER_SIGNAL ; 
 scalar_t__ WARN_ON (int) ; 
 int WL1271_MAX_RX_FILTERS ; 
 int wl1271_acx_default_rx_filter_enable (struct wl1271*,int,int /*<<< orphan*/ ) ; 
 int wl1271_convert_wowlan_pattern_to_rx_filter (struct cfg80211_pkt_pattern*,struct wl12xx_rx_filter**) ; 
 int wl1271_rx_filter_clear_all (struct wl1271*) ; 
 int wl1271_rx_filter_enable (struct wl1271*,int,int,struct wl12xx_rx_filter*) ; 
 int /*<<< orphan*/  wl1271_rx_filter_free (struct wl12xx_rx_filter*) ; 
 int wl1271_validate_wowlan_pattern (struct cfg80211_pkt_pattern*) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

__attribute__((used)) static int wl1271_configure_wowlan(struct wl1271 *wl,
				   struct cfg80211_wowlan *wow)
{
	int i, ret;

	if (!wow || wow->any || !wow->n_patterns) {
		ret = wl1271_acx_default_rx_filter_enable(wl, 0,
							  FILTER_SIGNAL);
		if (ret)
			goto out;

		ret = wl1271_rx_filter_clear_all(wl);
		if (ret)
			goto out;

		return 0;
	}

	if (WARN_ON(wow->n_patterns > WL1271_MAX_RX_FILTERS))
		return -EINVAL;

	/* Validate all incoming patterns before clearing current FW state */
	for (i = 0; i < wow->n_patterns; i++) {
		ret = wl1271_validate_wowlan_pattern(&wow->patterns[i]);
		if (ret) {
			wl1271_warning("Bad wowlan pattern %d", i);
			return ret;
		}
	}

	ret = wl1271_acx_default_rx_filter_enable(wl, 0, FILTER_SIGNAL);
	if (ret)
		goto out;

	ret = wl1271_rx_filter_clear_all(wl);
	if (ret)
		goto out;

	/* Translate WoWLAN patterns into filters */
	for (i = 0; i < wow->n_patterns; i++) {
		struct cfg80211_pkt_pattern *p;
		struct wl12xx_rx_filter *filter = NULL;

		p = &wow->patterns[i];

		ret = wl1271_convert_wowlan_pattern_to_rx_filter(p, &filter);
		if (ret) {
			wl1271_warning("Failed to create an RX filter from "
				       "wowlan pattern %d", i);
			goto out;
		}

		ret = wl1271_rx_filter_enable(wl, i, 1, filter);

		wl1271_rx_filter_free(filter);
		if (ret)
			goto out;
	}

	ret = wl1271_acx_default_rx_filter_enable(wl, 1, FILTER_DROP);

out:
	return ret;
}