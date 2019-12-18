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
struct element {scalar_t__ id; int datalen; int* data; } ;

/* Variables and functions */
 scalar_t__ WLAN_EID_EXTENSION ; 
 scalar_t__ WLAN_EID_MULTIPLE_BSSID ; 

bool cfg80211_is_element_inherited(const struct element *elem,
				   const struct element *non_inherit_elem)
{
	u8 id_len, ext_id_len, i, loop_len, id;
	const u8 *list;

	if (elem->id == WLAN_EID_MULTIPLE_BSSID)
		return false;

	if (!non_inherit_elem || non_inherit_elem->datalen < 2)
		return true;

	/*
	 * non inheritance element format is:
	 * ext ID (56) | IDs list len | list | extension IDs list len | list
	 * Both lists are optional. Both lengths are mandatory.
	 * This means valid length is:
	 * elem_len = 1 (extension ID) + 2 (list len fields) + list lengths
	 */
	id_len = non_inherit_elem->data[1];
	if (non_inherit_elem->datalen < 3 + id_len)
		return true;

	ext_id_len = non_inherit_elem->data[2 + id_len];
	if (non_inherit_elem->datalen < 3 + id_len + ext_id_len)
		return true;

	if (elem->id == WLAN_EID_EXTENSION) {
		if (!ext_id_len)
			return true;
		loop_len = ext_id_len;
		list = &non_inherit_elem->data[3 + id_len];
		id = elem->data[0];
	} else {
		if (!id_len)
			return true;
		loop_len = id_len;
		list = &non_inherit_elem->data[2];
		id = elem->id;
	}

	for (i = 0; i < loop_len; i++) {
		if (list[i] == id)
			return false;
	}

	return true;
}