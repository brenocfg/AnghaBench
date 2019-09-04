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

/* Variables and functions */
 char* ieee80211_regdom ; 
 scalar_t__ is_user_regdom_saved () ; 
 int /*<<< orphan*/  is_world_regdom (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 char* user_alpha2 ; 

__attribute__((used)) static void restore_alpha2(char *alpha2, bool reset_user)
{
	/* indicates there is no alpha2 to consider for restoration */
	alpha2[0] = '9';
	alpha2[1] = '7';

	/* The user setting has precedence over the module parameter */
	if (is_user_regdom_saved()) {
		/* Unless we're asked to ignore it and reset it */
		if (reset_user) {
			pr_debug("Restoring regulatory settings including user preference\n");
			user_alpha2[0] = '9';
			user_alpha2[1] = '7';

			/*
			 * If we're ignoring user settings, we still need to
			 * check the module parameter to ensure we put things
			 * back as they were for a full restore.
			 */
			if (!is_world_regdom(ieee80211_regdom)) {
				pr_debug("Keeping preference on module parameter ieee80211_regdom: %c%c\n",
					 ieee80211_regdom[0], ieee80211_regdom[1]);
				alpha2[0] = ieee80211_regdom[0];
				alpha2[1] = ieee80211_regdom[1];
			}
		} else {
			pr_debug("Restoring regulatory settings while preserving user preference for: %c%c\n",
				 user_alpha2[0], user_alpha2[1]);
			alpha2[0] = user_alpha2[0];
			alpha2[1] = user_alpha2[1];
		}
	} else if (!is_world_regdom(ieee80211_regdom)) {
		pr_debug("Keeping preference on module parameter ieee80211_regdom: %c%c\n",
			 ieee80211_regdom[0], ieee80211_regdom[1]);
		alpha2[0] = ieee80211_regdom[0];
		alpha2[1] = ieee80211_regdom[1];
	} else
		pr_debug("Restoring regulatory settings\n");
}