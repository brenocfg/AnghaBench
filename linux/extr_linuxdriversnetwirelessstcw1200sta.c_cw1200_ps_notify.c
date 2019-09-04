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
struct cw1200_common {int /*<<< orphan*/  vif; int /*<<< orphan*/  hw; int /*<<< orphan*/  sta_asleep_mask; } ;

/* Variables and functions */
 int CW1200_MAX_STA_IN_AP_MODE ; 
 int /*<<< orphan*/  STA_NOTIFY_AWAKE ; 
 int /*<<< orphan*/  STA_NOTIFY_SLEEP ; 
 int /*<<< orphan*/  __cw1200_sta_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cw1200_ps_notify(struct cw1200_common *priv,
		      int link_id, bool ps)
{
	if (link_id > CW1200_MAX_STA_IN_AP_MODE)
		return;

	pr_debug("%s for LinkId: %d. STAs asleep: %.8X\n",
		 ps ? "Stop" : "Start",
		 link_id, priv->sta_asleep_mask);

	__cw1200_sta_notify(priv->hw, priv->vif,
			    ps ? STA_NOTIFY_SLEEP : STA_NOTIFY_AWAKE, link_id);
}