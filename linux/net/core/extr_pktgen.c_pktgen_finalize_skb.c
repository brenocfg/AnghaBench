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
struct timespec64 {int tv_sec; int tv_nsec; } ;
struct sk_buff {int /*<<< orphan*/  data_len; int /*<<< orphan*/  len; } ;
struct pktgen_hdr {void* tv_usec; void* tv_sec; void* seq_num; void* pgh_magic; } ;
struct pktgen_dev {int nfrags; int node; int flags; int seq_num; int /*<<< orphan*/  page; } ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int F_NODE ; 
 int F_NO_TIMESTAMP ; 
 int GFP_KERNEL ; 
 int MAX_SKB_FRAGS ; 
 int NSEC_PER_USEC ; 
 int PAGE_SIZE ; 
 int PKTGEN_MAGIC ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  alloc_pages_node (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int numa_node_id () ; 
 int /*<<< orphan*/  skb_frag_off_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_set_page (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,int) ; 
 struct pktgen_hdr* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_zero (struct sk_buff*,int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void pktgen_finalize_skb(struct pktgen_dev *pkt_dev, struct sk_buff *skb,
				int datalen)
{
	struct timespec64 timestamp;
	struct pktgen_hdr *pgh;

	pgh = skb_put(skb, sizeof(*pgh));
	datalen -= sizeof(*pgh);

	if (pkt_dev->nfrags <= 0) {
		skb_put_zero(skb, datalen);
	} else {
		int frags = pkt_dev->nfrags;
		int i, len;
		int frag_len;


		if (frags > MAX_SKB_FRAGS)
			frags = MAX_SKB_FRAGS;
		len = datalen - frags * PAGE_SIZE;
		if (len > 0) {
			skb_put_zero(skb, len);
			datalen = frags * PAGE_SIZE;
		}

		i = 0;
		frag_len = (datalen/frags) < PAGE_SIZE ?
			   (datalen/frags) : PAGE_SIZE;
		while (datalen > 0) {
			if (unlikely(!pkt_dev->page)) {
				int node = numa_node_id();

				if (pkt_dev->node >= 0 && (pkt_dev->flags & F_NODE))
					node = pkt_dev->node;
				pkt_dev->page = alloc_pages_node(node, GFP_KERNEL | __GFP_ZERO, 0);
				if (!pkt_dev->page)
					break;
			}
			get_page(pkt_dev->page);
			skb_frag_set_page(skb, i, pkt_dev->page);
			skb_frag_off_set(&skb_shinfo(skb)->frags[i], 0);
			/*last fragment, fill rest of data*/
			if (i == (frags - 1))
				skb_frag_size_set(&skb_shinfo(skb)->frags[i],
				    (datalen < PAGE_SIZE ? datalen : PAGE_SIZE));
			else
				skb_frag_size_set(&skb_shinfo(skb)->frags[i], frag_len);
			datalen -= skb_frag_size(&skb_shinfo(skb)->frags[i]);
			skb->len += skb_frag_size(&skb_shinfo(skb)->frags[i]);
			skb->data_len += skb_frag_size(&skb_shinfo(skb)->frags[i]);
			i++;
			skb_shinfo(skb)->nr_frags = i;
		}
	}

	/* Stamp the time, and sequence number,
	 * convert them to network byte order
	 */
	pgh->pgh_magic = htonl(PKTGEN_MAGIC);
	pgh->seq_num = htonl(pkt_dev->seq_num);

	if (pkt_dev->flags & F_NO_TIMESTAMP) {
		pgh->tv_sec = 0;
		pgh->tv_usec = 0;
	} else {
		/*
		 * pgh->tv_sec wraps in y2106 when interpreted as unsigned
		 * as done by wireshark, or y2038 when interpreted as signed.
		 * This is probably harmless, but if anyone wants to improve
		 * it, we could introduce a variant that puts 64-bit nanoseconds
		 * into the respective header bytes.
		 * This would also be slightly faster to read.
		 */
		ktime_get_real_ts64(&timestamp);
		pgh->tv_sec = htonl(timestamp.tv_sec);
		pgh->tv_usec = htonl(timestamp.tv_nsec / NSEC_PER_USEC);
	}
}