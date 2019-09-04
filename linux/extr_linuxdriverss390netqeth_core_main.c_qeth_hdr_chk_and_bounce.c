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
struct sk_buff {int data; int tail; } ;
struct qeth_hdr {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 int skb_headroom (struct sk_buff*) ; 

int qeth_hdr_chk_and_bounce(struct sk_buff *skb, struct qeth_hdr **hdr, int len)
{
	int hroom, inpage, rest;

	if (((unsigned long)skb->data & PAGE_MASK) !=
	    (((unsigned long)skb->data + len - 1) & PAGE_MASK)) {
		hroom = skb_headroom(skb);
		inpage = PAGE_SIZE - ((unsigned long) skb->data % PAGE_SIZE);
		rest = len - inpage;
		if (rest > hroom)
			return 1;
		memmove(skb->data - rest, skb->data, skb_headlen(skb));
		skb->data -= rest;
		skb->tail -= rest;
		*hdr = (struct qeth_hdr *)skb->data;
		QETH_DBF_MESSAGE(2, "skb bounce len: %d rest: %d\n", len, rest);
	}
	return 0;
}