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
struct TYPE_3__ {TYPE_2__* wowlan_config; } ;
struct cfg80211_registered_device {TYPE_1__ wiphy; } ;
struct TYPE_4__ {int n_patterns; struct TYPE_4__* nd_config; struct TYPE_4__* tcp; scalar_t__ sock; struct TYPE_4__* patterns; struct TYPE_4__* mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  sock_release (scalar_t__) ; 

__attribute__((used)) static inline void
cfg80211_rdev_free_wowlan(struct cfg80211_registered_device *rdev)
{
#ifdef CONFIG_PM
	int i;

	if (!rdev->wiphy.wowlan_config)
		return;
	for (i = 0; i < rdev->wiphy.wowlan_config->n_patterns; i++)
		kfree(rdev->wiphy.wowlan_config->patterns[i].mask);
	kfree(rdev->wiphy.wowlan_config->patterns);
	if (rdev->wiphy.wowlan_config->tcp &&
	    rdev->wiphy.wowlan_config->tcp->sock)
		sock_release(rdev->wiphy.wowlan_config->tcp->sock);
	kfree(rdev->wiphy.wowlan_config->tcp);
	kfree(rdev->wiphy.wowlan_config->nd_config);
	kfree(rdev->wiphy.wowlan_config);
#endif
}