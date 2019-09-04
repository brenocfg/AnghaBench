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
struct sockaddr_qrtr {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct sk_buff {int dummy; } ;
struct qrtr_node {int /*<<< orphan*/  ep_lock; int /*<<< orphan*/ * ep; int /*<<< orphan*/  nid; } ;
struct qrtr_endpoint {struct qrtr_node* node; } ;
struct qrtr_ctrl_pkt {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_QIPCRTR ; 
 int /*<<< orphan*/  QRTR_PORT_CTRL ; 
 int /*<<< orphan*/  QRTR_TYPE_BYE ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* qrtr_alloc_ctrl_packet (struct qrtr_ctrl_pkt**) ; 
 int /*<<< orphan*/  qrtr_local_enqueue (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,struct sockaddr_qrtr*,struct sockaddr_qrtr*) ; 
 int /*<<< orphan*/  qrtr_local_nid ; 
 int /*<<< orphan*/  qrtr_node_release (struct qrtr_node*) ; 

void qrtr_endpoint_unregister(struct qrtr_endpoint *ep)
{
	struct qrtr_node *node = ep->node;
	struct sockaddr_qrtr src = {AF_QIPCRTR, node->nid, QRTR_PORT_CTRL};
	struct sockaddr_qrtr dst = {AF_QIPCRTR, qrtr_local_nid, QRTR_PORT_CTRL};
	struct qrtr_ctrl_pkt *pkt;
	struct sk_buff *skb;

	mutex_lock(&node->ep_lock);
	node->ep = NULL;
	mutex_unlock(&node->ep_lock);

	/* Notify the local controller about the event */
	skb = qrtr_alloc_ctrl_packet(&pkt);
	if (skb) {
		pkt->cmd = cpu_to_le32(QRTR_TYPE_BYE);
		qrtr_local_enqueue(NULL, skb, QRTR_TYPE_BYE, &src, &dst);
	}

	qrtr_node_release(node);
	ep->node = NULL;
}