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
struct survey_info {int /*<<< orphan*/  noise; int /*<<< orphan*/  filled; int /*<<< orphan*/  channel; } ;
struct lbtf_private {int /*<<< orphan*/  noise; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct ieee80211_conf {TYPE_1__ chandef; } ;
struct ieee80211_hw {struct ieee80211_conf conf; struct lbtf_private* priv; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  SURVEY_INFO_NOISE_DBM ; 

__attribute__((used)) static int lbtf_op_get_survey(struct ieee80211_hw *hw, int idx,
				struct survey_info *survey)
{
	struct lbtf_private *priv = hw->priv;
	struct ieee80211_conf *conf = &hw->conf;

	if (idx != 0)
		return -ENOENT;

	survey->channel = conf->chandef.chan;
	survey->filled = SURVEY_INFO_NOISE_DBM;
	survey->noise = priv->noise;

	return 0;
}