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
struct sk_buff {scalar_t__ protocol; scalar_t__ data; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct qeth_hdr {int dummy; } ;
struct qeth_card {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int qeth_do_send_packet (struct qeth_card*,struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int qeth_get_elements_no (struct qeth_card*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_hdr_chk_and_bounce (struct sk_buff*,struct qeth_hdr**,int) ; 

__attribute__((used)) static int qeth_l2_xmit_osn(struct qeth_card *card, struct sk_buff *skb,
			    struct qeth_qdio_out_q *queue)
{
	unsigned int elements;
	struct qeth_hdr *hdr;

	if (skb->protocol == htons(ETH_P_IPV6))
		return -EPROTONOSUPPORT;

	hdr = (struct qeth_hdr *)skb->data;
	elements = qeth_get_elements_no(card, skb, 0, 0);
	if (!elements)
		return -E2BIG;
	if (qeth_hdr_chk_and_bounce(skb, &hdr, sizeof(*hdr)))
		return -EINVAL;
	return qeth_do_send_packet(card, queue, skb, hdr, 0, 0, elements);
}