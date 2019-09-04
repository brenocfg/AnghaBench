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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct qeth_card {int dummy; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int,int /*<<< orphan*/ ) ; 
 int QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 int qeth_get_elements_for_frags (struct sk_buff*) ; 
 scalar_t__ qeth_get_elements_for_range (scalar_t__,scalar_t__) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 scalar_t__ tcp_hdr (struct sk_buff*) ; 
 scalar_t__ tcp_hdrlen (struct sk_buff*) ; 

__attribute__((used)) static int qeth_l3_get_elements_no_tso(struct qeth_card *card,
			struct sk_buff *skb, int extra_elems)
{
	addr_t start = (addr_t)tcp_hdr(skb) + tcp_hdrlen(skb);
	addr_t end = (addr_t)skb->data + skb_headlen(skb);
	int elements = qeth_get_elements_for_frags(skb);

	if (start != end)
		elements += qeth_get_elements_for_range(start, end);

	if ((elements + extra_elems) > QETH_MAX_BUFFER_ELEMENTS(card)) {
		QETH_DBF_MESSAGE(2,
	"Invalid size of TSO IP packet (Number=%d / Length=%d). Discarded.\n",
				elements + extra_elems, skb->len);
		return 0;
	}
	return elements;
}