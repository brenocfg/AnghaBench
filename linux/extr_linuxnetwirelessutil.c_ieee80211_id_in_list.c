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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ const WLAN_EID_EXTENSION ; 

__attribute__((used)) static bool ieee80211_id_in_list(const u8 *ids, int n_ids, u8 id, bool id_ext)
{
	int i;

	/* Make sure array values are legal */
	if (WARN_ON(ids[n_ids - 1] == WLAN_EID_EXTENSION))
		return false;

	i = 0;
	while (i < n_ids) {
		if (ids[i] == WLAN_EID_EXTENSION) {
			if (id_ext && (ids[i + 1] == id))
				return true;

			i += 2;
			continue;
		}

		if (ids[i] == id && !id_ext)
			return true;

		i++;
	}
	return false;
}