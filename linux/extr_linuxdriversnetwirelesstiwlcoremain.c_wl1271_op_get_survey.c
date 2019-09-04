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
struct survey_info {scalar_t__ filled; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct ieee80211_conf {TYPE_1__ chandef; } ;
struct ieee80211_hw {struct ieee80211_conf conf; } ;

/* Variables and functions */
 int ENOENT ; 

__attribute__((used)) static int wl1271_op_get_survey(struct ieee80211_hw *hw, int idx,
				struct survey_info *survey)
{
	struct ieee80211_conf *conf = &hw->conf;

	if (idx != 0)
		return -ENOENT;

	survey->channel = conf->chandef.chan;
	survey->filled = 0;
	return 0;
}