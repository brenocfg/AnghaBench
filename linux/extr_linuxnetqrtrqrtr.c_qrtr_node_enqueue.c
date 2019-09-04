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
struct sockaddr_qrtr {size_t sq_node; size_t sq_port; } ;
struct sk_buff {size_t len; } ;
struct qrtr_node {size_t nid; int /*<<< orphan*/  ep_lock; TYPE_1__* ep; } ;
struct qrtr_hdr_v1 {scalar_t__ confirm_rx; void* size; void* dst_port_id; void* dst_node_id; void* src_port_id; void* src_node_id; void* type; void* version; } ;
struct TYPE_2__ {int (* xmit ) (TYPE_1__*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (size_t,int) ; 
 int ENODEV ; 
 size_t QRTR_NODE_BCAST ; 
 size_t QRTR_PORT_CTRL ; 
 size_t QRTR_PROTO_VER_1 ; 
 void* cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct qrtr_hdr_v1* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_padto (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,struct sk_buff*) ; 

__attribute__((used)) static int qrtr_node_enqueue(struct qrtr_node *node, struct sk_buff *skb,
			     int type, struct sockaddr_qrtr *from,
			     struct sockaddr_qrtr *to)
{
	struct qrtr_hdr_v1 *hdr;
	size_t len = skb->len;
	int rc = -ENODEV;

	hdr = skb_push(skb, sizeof(*hdr));
	hdr->version = cpu_to_le32(QRTR_PROTO_VER_1);
	hdr->type = cpu_to_le32(type);
	hdr->src_node_id = cpu_to_le32(from->sq_node);
	hdr->src_port_id = cpu_to_le32(from->sq_port);
	if (to->sq_port == QRTR_PORT_CTRL) {
		hdr->dst_node_id = cpu_to_le32(node->nid);
		hdr->dst_port_id = cpu_to_le32(QRTR_NODE_BCAST);
	} else {
		hdr->dst_node_id = cpu_to_le32(to->sq_node);
		hdr->dst_port_id = cpu_to_le32(to->sq_port);
	}

	hdr->size = cpu_to_le32(len);
	hdr->confirm_rx = 0;

	skb_put_padto(skb, ALIGN(len, 4));

	mutex_lock(&node->ep_lock);
	if (node->ep)
		rc = node->ep->xmit(node->ep, skb);
	else
		kfree_skb(skb);
	mutex_unlock(&node->ep_lock);

	return rc;
}