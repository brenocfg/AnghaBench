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
struct p54_common {int update_stats; int /*<<< orphan*/  stat_comp; } ;
struct ieee80211_hw {struct p54_common* priv; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int p54_fetch_statistics (struct p54_common*) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int p54_wait_for_stats(struct ieee80211_hw *dev)
{
	struct p54_common *priv = dev->priv;
	int ret;

	priv->update_stats = true;
	ret = p54_fetch_statistics(priv);
	if (ret)
		return ret;

	ret = wait_for_completion_interruptible_timeout(&priv->stat_comp, HZ);
	if (ret == 0)
		return -ETIMEDOUT;

	return 0;
}