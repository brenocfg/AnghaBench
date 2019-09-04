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
struct xennet_gnttab_make_txreq {struct xen_netif_tx_request* tx; int /*<<< orphan*/  size; struct page* page; struct sk_buff* skb; struct netfront_queue* queue; } ;
struct xen_netif_tx_request {int dummy; } ;
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct netfront_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnttab_for_one_grant (struct page*,unsigned int,unsigned int,int /*<<< orphan*/ ,struct xennet_gnttab_make_txreq*) ; 
 int /*<<< orphan*/  xennet_tx_setup_grant ; 

__attribute__((used)) static struct xen_netif_tx_request *xennet_make_first_txreq(
	struct netfront_queue *queue, struct sk_buff *skb,
	struct page *page, unsigned int offset, unsigned int len)
{
	struct xennet_gnttab_make_txreq info = {
		.queue = queue,
		.skb = skb,
		.page = page,
		.size = 0,
	};

	gnttab_for_one_grant(page, offset, len, xennet_tx_setup_grant, &info);

	return info.tx;
}