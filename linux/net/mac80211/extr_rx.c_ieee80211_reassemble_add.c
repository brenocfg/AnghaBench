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
struct sk_buff {int dummy; } ;
struct ieee80211_sub_if_data {scalar_t__ fragment_next; struct ieee80211_fragment_entry* fragments; } ;
struct ieee80211_fragment_entry {unsigned int seq; int rx_queue; unsigned int last_frag; int check_sequential_pn; scalar_t__ extra_len; int /*<<< orphan*/  first_frag_time; int /*<<< orphan*/  skb_list; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_FRAGMENT_MAX ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct ieee80211_fragment_entry *
ieee80211_reassemble_add(struct ieee80211_sub_if_data *sdata,
			 unsigned int frag, unsigned int seq, int rx_queue,
			 struct sk_buff **skb)
{
	struct ieee80211_fragment_entry *entry;

	entry = &sdata->fragments[sdata->fragment_next++];
	if (sdata->fragment_next >= IEEE80211_FRAGMENT_MAX)
		sdata->fragment_next = 0;

	if (!skb_queue_empty(&entry->skb_list))
		__skb_queue_purge(&entry->skb_list);

	__skb_queue_tail(&entry->skb_list, *skb); /* no need for locking */
	*skb = NULL;
	entry->first_frag_time = jiffies;
	entry->seq = seq;
	entry->rx_queue = rx_queue;
	entry->last_frag = frag;
	entry->check_sequential_pn = false;
	entry->extra_len = 0;

	return entry;
}