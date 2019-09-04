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
typedef  int u8 ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  memcmp (int const*,int const*,int) ; 

const u8 *cfg80211_find_ie_match(u8 eid, const u8 *ies, int len,
				 const u8 *match, int match_len,
				 int match_offset)
{
	/* match_offset can't be smaller than 2, unless match_len is
	 * zero, in which case match_offset must be zero as well.
	 */
	if (WARN_ON((match_len && match_offset < 2) ||
		    (!match_len && match_offset)))
		return NULL;

	while (len >= 2 && len >= ies[1] + 2) {
		if ((ies[0] == eid) &&
		    (ies[1] + 2 >= match_offset + match_len) &&
		    !memcmp(ies + match_offset, match, match_len))
			return ies;

		len -= ies[1] + 2;
		ies += ies[1] + 2;
	}

	return NULL;
}