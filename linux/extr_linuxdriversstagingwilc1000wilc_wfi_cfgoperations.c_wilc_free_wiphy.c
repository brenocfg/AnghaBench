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
struct net_device {TYPE_1__* ieee80211_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  wiphy_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_unregister (int /*<<< orphan*/ ) ; 

void wilc_free_wiphy(struct net_device *net)
{
	if (!net)
		return;

	if (!net->ieee80211_ptr)
		return;

	if (!net->ieee80211_ptr->wiphy)
		return;

	wiphy_unregister(net->ieee80211_ptr->wiphy);

	wiphy_free(net->ieee80211_ptr->wiphy);
	kfree(net->ieee80211_ptr);
}