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
struct p54_common {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  coverage_class; } ;
struct ieee80211_hw {struct p54_common* priv; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  clamp_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54_set_edcf (struct p54_common*) ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static void p54_set_coverage_class(struct ieee80211_hw *dev,
				   s16 coverage_class)
{
	struct p54_common *priv = dev->priv;

	mutex_lock(&priv->conf_mutex);
	/* support all coverage class values as in 802.11-2007 Table 7-27 */
	priv->coverage_class = clamp_t(u8, coverage_class, 0, 31);
	p54_set_edcf(priv);
	mutex_unlock(&priv->conf_mutex);
}