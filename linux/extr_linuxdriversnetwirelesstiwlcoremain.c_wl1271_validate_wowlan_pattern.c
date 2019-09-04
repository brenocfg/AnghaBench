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
struct cfg80211_pkt_pattern {int pattern_len; scalar_t__ mask; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 scalar_t__ RX_FILTER_FIELD_OVERHEAD ; 
 int WL1271_RX_FILTER_ETH_HEADER_SIZE ; 
 int WL1271_RX_FILTER_MAX_FIELDS ; 
 int WL1271_RX_FILTER_MAX_FIELDS_SIZE ; 
 scalar_t__ test_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 

__attribute__((used)) static int
wl1271_validate_wowlan_pattern(struct cfg80211_pkt_pattern *p)
{
	int num_fields = 0, in_field = 0, fields_size = 0;
	int i, pattern_len = 0;

	if (!p->mask) {
		wl1271_warning("No mask in WoWLAN pattern");
		return -EINVAL;
	}

	/*
	 * The pattern is broken up into segments of bytes at different offsets
	 * that need to be checked by the FW filter. Each segment is called
	 * a field in the FW API. We verify that the total number of fields
	 * required for this pattern won't exceed FW limits (8)
	 * as well as the total fields buffer won't exceed the FW limit.
	 * Note that if there's a pattern which crosses Ethernet/IP header
	 * boundary a new field is required.
	 */
	for (i = 0; i < p->pattern_len; i++) {
		if (test_bit(i, (unsigned long *)p->mask)) {
			if (!in_field) {
				in_field = 1;
				pattern_len = 1;
			} else {
				if (i == WL1271_RX_FILTER_ETH_HEADER_SIZE) {
					num_fields++;
					fields_size += pattern_len +
						RX_FILTER_FIELD_OVERHEAD;
					pattern_len = 1;
				} else
					pattern_len++;
			}
		} else {
			if (in_field) {
				in_field = 0;
				fields_size += pattern_len +
					RX_FILTER_FIELD_OVERHEAD;
				num_fields++;
			}
		}
	}

	if (in_field) {
		fields_size += pattern_len + RX_FILTER_FIELD_OVERHEAD;
		num_fields++;
	}

	if (num_fields > WL1271_RX_FILTER_MAX_FIELDS) {
		wl1271_warning("RX Filter too complex. Too many segments");
		return -EINVAL;
	}

	if (fields_size > WL1271_RX_FILTER_MAX_FIELDS_SIZE) {
		wl1271_warning("RX filter pattern is too big");
		return -E2BIG;
	}

	return 0;
}