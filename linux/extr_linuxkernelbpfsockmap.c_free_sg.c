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
struct sock {int dummy; } ;
struct sk_msg_buff {scalar_t__ skb; struct scatterlist* sg_data; } ;
struct scatterlist {scalar_t__ offset; scalar_t__ page_link; scalar_t__ length; } ;

/* Variables and functions */
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  consume_skb (scalar_t__) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,scalar_t__) ; 

__attribute__((used)) static int free_sg(struct sock *sk, int start,
		   struct sk_msg_buff *md, bool charge)
{
	struct scatterlist *sg = md->sg_data;
	int i = start, free = 0;

	while (sg[i].length) {
		free += sg[i].length;
		if (charge)
			sk_mem_uncharge(sk, sg[i].length);
		if (!md->skb)
			put_page(sg_page(&sg[i]));
		sg[i].length = 0;
		sg[i].page_link = 0;
		sg[i].offset = 0;
		i++;

		if (i == MAX_SKB_FRAGS)
			i = 0;
	}
	if (md->skb)
		consume_skb(md->skb);

	return free;
}