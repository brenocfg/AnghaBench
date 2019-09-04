#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wireless_dev {TYPE_3__* wiphy; } ;
struct wilc_priv {int dummy; } ;
struct TYPE_5__ {int* rx_mask; } ;
struct TYPE_6__ {int ht_supported; int cap; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; TYPE_1__ mcs; } ;
struct TYPE_8__ {TYPE_2__ ht_cap; } ;
struct TYPE_7__ {TYPE_4__** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int /*<<< orphan*/  IEEE80211_HT_MAX_AMPDU_8K ; 
 int /*<<< orphan*/  IEEE80211_HT_MPDU_DENSITY_NONE ; 
 size_t NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  kfree (struct wireless_dev*) ; 
 struct wireless_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ wilc_band_2ghz ; 
 int /*<<< orphan*/  wilc_cfg80211_ops ; 
 TYPE_3__* wiphy_new (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct wireless_dev *wilc_wfi_cfg_alloc(void)
{
	struct wireless_dev *wdev;

	wdev = kzalloc(sizeof(*wdev), GFP_KERNEL);
	if (!wdev)
		goto out;

	wdev->wiphy = wiphy_new(&wilc_cfg80211_ops, sizeof(struct wilc_priv));
	if (!wdev->wiphy)
		goto free_mem;

	wilc_band_2ghz.ht_cap.ht_supported = 1;
	wilc_band_2ghz.ht_cap.cap |= (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);
	wilc_band_2ghz.ht_cap.mcs.rx_mask[0] = 0xff;
	wilc_band_2ghz.ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_8K;
	wilc_band_2ghz.ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE;

	wdev->wiphy->bands[NL80211_BAND_2GHZ] = &wilc_band_2ghz;

	return wdev;

free_mem:
	kfree(wdev);
out:
	return NULL;
}