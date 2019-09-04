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
struct virtnet_rq_stats {int /*<<< orphan*/  drops; int /*<<< orphan*/  bytes; } ;
struct virtnet_info {unsigned int hdr_len; } ;
struct sk_buff {int dummy; } ;
struct receive_queue {int dummy; } ;
struct page {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  give_pages (struct receive_queue*,struct page*) ; 
 struct sk_buff* page_to_skb (struct virtnet_info*,struct receive_queue*,struct page*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *receive_big(struct net_device *dev,
				   struct virtnet_info *vi,
				   struct receive_queue *rq,
				   void *buf,
				   unsigned int len,
				   struct virtnet_rq_stats *stats)
{
	struct page *page = buf;
	struct sk_buff *skb = page_to_skb(vi, rq, page, 0, len,
					  PAGE_SIZE, true);

	stats->bytes += len - vi->hdr_len;
	if (unlikely(!skb))
		goto err;

	return skb;

err:
	stats->drops++;
	give_pages(rq, page);
	return NULL;
}