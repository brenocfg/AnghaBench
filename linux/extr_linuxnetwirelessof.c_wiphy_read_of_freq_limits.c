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
typedef  int /*<<< orphan*/  u32 ;
struct wiphy {int dummy; } ;
struct property {int dummy; } ;
struct ieee80211_freq_range {scalar_t__ start_freq_khz; scalar_t__ end_freq_khz; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct device_node* dev_of_node (struct device*) ; 
 struct ieee80211_freq_range* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_freq_range*) ; 
 struct property* of_find_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/ * of_prop_next_u32 (struct property*,int /*<<< orphan*/  const*,scalar_t__*) ; 
 struct device* wiphy_dev (struct wiphy*) ; 
 int /*<<< orphan*/  wiphy_freq_limits_apply (struct wiphy*,struct ieee80211_freq_range*,unsigned int) ; 

void wiphy_read_of_freq_limits(struct wiphy *wiphy)
{
	struct device *dev = wiphy_dev(wiphy);
	struct device_node *np;
	struct property *prop;
	struct ieee80211_freq_range *freq_limits;
	unsigned int n_freq_limits;
	const __be32 *p;
	int len, i;
	int err = 0;

	if (!dev)
		return;
	np = dev_of_node(dev);
	if (!np)
		return;

	prop = of_find_property(np, "ieee80211-freq-limit", &len);
	if (!prop)
		return;

	if (!len || len % sizeof(u32) || len / sizeof(u32) % 2) {
		dev_err(dev, "ieee80211-freq-limit wrong format");
		return;
	}
	n_freq_limits = len / sizeof(u32) / 2;

	freq_limits = kcalloc(n_freq_limits, sizeof(*freq_limits), GFP_KERNEL);
	if (!freq_limits) {
		err = -ENOMEM;
		goto out_kfree;
	}

	p = NULL;
	for (i = 0; i < n_freq_limits; i++) {
		struct ieee80211_freq_range *limit = &freq_limits[i];

		p = of_prop_next_u32(prop, p, &limit->start_freq_khz);
		if (!p) {
			err = -EINVAL;
			goto out_kfree;
		}

		p = of_prop_next_u32(prop, p, &limit->end_freq_khz);
		if (!p) {
			err = -EINVAL;
			goto out_kfree;
		}

		if (!limit->start_freq_khz ||
		    !limit->end_freq_khz ||
		    limit->start_freq_khz >= limit->end_freq_khz) {
			err = -EINVAL;
			goto out_kfree;
		}
	}

	wiphy_freq_limits_apply(wiphy, freq_limits, n_freq_limits);

out_kfree:
	kfree(freq_limits);
	if (err)
		dev_err(dev, "Failed to get limits: %d\n", err);
}