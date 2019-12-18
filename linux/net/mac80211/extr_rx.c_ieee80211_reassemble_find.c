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
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_sub_if_data {int fragment_next; struct ieee80211_fragment_entry* fragments; } ;
struct ieee80211_hdr {int frame_control; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; } ;
struct ieee80211_fragment_entry {unsigned int seq; int rx_queue; int last_frag; int /*<<< orphan*/  skb_list; scalar_t__ first_frag_time; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FRAGMENT_MAX ; 
 struct sk_buff* __skb_peek (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline struct ieee80211_fragment_entry *
ieee80211_reassemble_find(struct ieee80211_sub_if_data *sdata,
			  unsigned int frag, unsigned int seq,
			  int rx_queue, struct ieee80211_hdr *hdr)
{
	struct ieee80211_fragment_entry *entry;
	int i, idx;

	idx = sdata->fragment_next;
	for (i = 0; i < IEEE80211_FRAGMENT_MAX; i++) {
		struct ieee80211_hdr *f_hdr;
		struct sk_buff *f_skb;

		idx--;
		if (idx < 0)
			idx = IEEE80211_FRAGMENT_MAX - 1;

		entry = &sdata->fragments[idx];
		if (skb_queue_empty(&entry->skb_list) || entry->seq != seq ||
		    entry->rx_queue != rx_queue ||
		    entry->last_frag + 1 != frag)
			continue;

		f_skb = __skb_peek(&entry->skb_list);
		f_hdr = (struct ieee80211_hdr *) f_skb->data;

		/*
		 * Check ftype and addresses are equal, else check next fragment
		 */
		if (((hdr->frame_control ^ f_hdr->frame_control) &
		     cpu_to_le16(IEEE80211_FCTL_FTYPE)) ||
		    !ether_addr_equal(hdr->addr1, f_hdr->addr1) ||
		    !ether_addr_equal(hdr->addr2, f_hdr->addr2))
			continue;

		if (time_after(jiffies, entry->first_frag_time + 2 * HZ)) {
			__skb_queue_purge(&entry->skb_list);
			continue;
		}
		return entry;
	}

	return NULL;
}