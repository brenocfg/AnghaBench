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
struct wiphy {int /*<<< orphan*/  privid; } ;
struct orinoco_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  orinoco_wiphy_privid ; 
 int /*<<< orphan*/  set_wiphy_dev (struct wiphy*,int /*<<< orphan*/ ) ; 
 struct orinoco_private* wiphy_priv (struct wiphy*) ; 

void orinoco_wiphy_init(struct wiphy *wiphy)
{
	struct orinoco_private *priv = wiphy_priv(wiphy);

	wiphy->privid = orinoco_wiphy_privid;

	set_wiphy_dev(wiphy, priv->dev);
}