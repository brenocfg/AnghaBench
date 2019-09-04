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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211_radiotap_vendor_namespaces {int dummy; } ;
struct ieee80211_radiotap_iterator {int _max_length; int _bitmap_shifter; int is_radiotap_ns; int /*<<< orphan*/ * _arg; int /*<<< orphan*/ * this_arg; struct ieee80211_radiotap_header* _rtheader; int /*<<< orphan*/ * current_namespace; struct ieee80211_radiotap_vendor_namespaces const* _vns; int /*<<< orphan*/ * _next_bitmap; scalar_t__ _reset_on_ext; scalar_t__ _arg_index; } ;
struct ieee80211_radiotap_header {int /*<<< orphan*/  it_present; int /*<<< orphan*/  it_len; scalar_t__ it_version; } ;

/* Variables and functions */
 int EINVAL ; 
 int IEEE80211_RADIOTAP_EXT ; 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int get_unaligned_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radiotap_ns ; 

int ieee80211_radiotap_iterator_init(
	struct ieee80211_radiotap_iterator *iterator,
	struct ieee80211_radiotap_header *radiotap_header,
	int max_length, const struct ieee80211_radiotap_vendor_namespaces *vns)
{
	/* check the radiotap header can actually be present */
	if (max_length < sizeof(struct ieee80211_radiotap_header))
		return -EINVAL;

	/* Linux only supports version 0 radiotap format */
	if (radiotap_header->it_version)
		return -EINVAL;

	/* sanity check for allowed length and radiotap length field */
	if (max_length < get_unaligned_le16(&radiotap_header->it_len))
		return -EINVAL;

	iterator->_rtheader = radiotap_header;
	iterator->_max_length = get_unaligned_le16(&radiotap_header->it_len);
	iterator->_arg_index = 0;
	iterator->_bitmap_shifter = get_unaligned_le32(&radiotap_header->it_present);
	iterator->_arg = (uint8_t *)radiotap_header + sizeof(*radiotap_header);
	iterator->_reset_on_ext = 0;
	iterator->_next_bitmap = &radiotap_header->it_present;
	iterator->_next_bitmap++;
	iterator->_vns = vns;
	iterator->current_namespace = &radiotap_ns;
	iterator->is_radiotap_ns = 1;

	/* find payload start allowing for extended bitmap(s) */

	if (iterator->_bitmap_shifter & (1<<IEEE80211_RADIOTAP_EXT)) {
		if ((unsigned long)iterator->_arg -
		    (unsigned long)iterator->_rtheader + sizeof(uint32_t) >
		    (unsigned long)iterator->_max_length)
			return -EINVAL;
		while (get_unaligned_le32(iterator->_arg) &
					(1 << IEEE80211_RADIOTAP_EXT)) {
			iterator->_arg += sizeof(uint32_t);

			/*
			 * check for insanity where the present bitmaps
			 * keep claiming to extend up to or even beyond the
			 * stated radiotap header length
			 */

			if ((unsigned long)iterator->_arg -
			    (unsigned long)iterator->_rtheader +
			    sizeof(uint32_t) >
			    (unsigned long)iterator->_max_length)
				return -EINVAL;
		}

		iterator->_arg += sizeof(uint32_t);

		/*
		 * no need to check again for blowing past stated radiotap
		 * header length, because ieee80211_radiotap_iterator_next
		 * checks it before it is dereferenced
		 */
	}

	iterator->this_arg = iterator->_arg;

	/* we are all initialized happily */

	return 0;
}