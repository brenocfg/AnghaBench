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
struct sk_buff {int /*<<< orphan*/ * next; } ;
struct nfqnl_instance {int dummy; } ;
struct nf_queue_entry {struct sk_buff* skb; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int __nfqnl_enqueue_packet (struct net*,struct nfqnl_instance*,struct nf_queue_entry*) ; 
 int /*<<< orphan*/  free_entry (struct nf_queue_entry*) ; 
 int /*<<< orphan*/  nf_bridge_adjust_segmented_data (struct sk_buff*) ; 
 struct nf_queue_entry* nf_queue_entry_dup (struct nf_queue_entry*) ; 
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff*) ; 

__attribute__((used)) static int
__nfqnl_enqueue_packet_gso(struct net *net, struct nfqnl_instance *queue,
			   struct sk_buff *skb, struct nf_queue_entry *entry)
{
	int ret = -ENOMEM;
	struct nf_queue_entry *entry_seg;

	nf_bridge_adjust_segmented_data(skb);

	if (skb->next == NULL) { /* last packet, no need to copy entry */
		struct sk_buff *gso_skb = entry->skb;
		entry->skb = skb;
		ret = __nfqnl_enqueue_packet(net, queue, entry);
		if (ret)
			entry->skb = gso_skb;
		return ret;
	}

	skb_mark_not_on_list(skb);

	entry_seg = nf_queue_entry_dup(entry);
	if (entry_seg) {
		entry_seg->skb = skb;
		ret = __nfqnl_enqueue_packet(net, queue, entry_seg);
		if (ret)
			free_entry(entry_seg);
	}
	return ret;
}