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
struct wiphy {int dummy; } ;
struct wilc_priv {int /*<<< orphan*/  pmkid_list; } ;
struct net_device {int dummy; } ;
struct host_if_pmkid_attr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int flush_pmksa(struct wiphy *wiphy, struct net_device *netdev)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);

	memset(&priv->pmkid_list, 0, sizeof(struct host_if_pmkid_attr));

	return 0;
}