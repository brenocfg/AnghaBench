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
typedef  unsigned int u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ cb; } ;
struct qrtr_node {int /*<<< orphan*/  work; int /*<<< orphan*/  rx_queue; } ;
struct qrtr_hdr_v2 {scalar_t__ type; int flags; int /*<<< orphan*/  size; int /*<<< orphan*/  dst_port_id; int /*<<< orphan*/  dst_node_id; int /*<<< orphan*/  src_port_id; int /*<<< orphan*/  src_node_id; int /*<<< orphan*/  optlen; } ;
struct qrtr_hdr_v1 {int /*<<< orphan*/  size; int /*<<< orphan*/  dst_port_id; int /*<<< orphan*/  dst_node_id; int /*<<< orphan*/  confirm_rx; int /*<<< orphan*/  src_port_id; int /*<<< orphan*/  src_node_id; int /*<<< orphan*/  type; } ;
struct qrtr_endpoint {struct qrtr_node* node; } ;
struct qrtr_cb {scalar_t__ type; scalar_t__ src_port; int confirm_rx; scalar_t__ dst_port; void* dst_node; void* src_node; } ;

/* Variables and functions */
 size_t ALIGN (unsigned int,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int QRTR_FLAGS_CONFIRM_RX ; 
 scalar_t__ QRTR_PORT_CTRL ; 
#define  QRTR_PROTO_VER_1 129 
#define  QRTR_PROTO_VER_2 128 
 scalar_t__ QRTR_TYPE_DATA ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,void const*,unsigned int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int qrtr_endpoint_post(struct qrtr_endpoint *ep, const void *data, size_t len)
{
	struct qrtr_node *node = ep->node;
	const struct qrtr_hdr_v1 *v1;
	const struct qrtr_hdr_v2 *v2;
	struct sk_buff *skb;
	struct qrtr_cb *cb;
	unsigned int size;
	unsigned int ver;
	size_t hdrlen;

	if (len & 3)
		return -EINVAL;

	skb = netdev_alloc_skb(NULL, len);
	if (!skb)
		return -ENOMEM;

	cb = (struct qrtr_cb *)skb->cb;

	/* Version field in v1 is little endian, so this works for both cases */
	ver = *(u8*)data;

	switch (ver) {
	case QRTR_PROTO_VER_1:
		v1 = data;
		hdrlen = sizeof(*v1);

		cb->type = le32_to_cpu(v1->type);
		cb->src_node = le32_to_cpu(v1->src_node_id);
		cb->src_port = le32_to_cpu(v1->src_port_id);
		cb->confirm_rx = !!v1->confirm_rx;
		cb->dst_node = le32_to_cpu(v1->dst_node_id);
		cb->dst_port = le32_to_cpu(v1->dst_port_id);

		size = le32_to_cpu(v1->size);
		break;
	case QRTR_PROTO_VER_2:
		v2 = data;
		hdrlen = sizeof(*v2) + v2->optlen;

		cb->type = v2->type;
		cb->confirm_rx = !!(v2->flags & QRTR_FLAGS_CONFIRM_RX);
		cb->src_node = le16_to_cpu(v2->src_node_id);
		cb->src_port = le16_to_cpu(v2->src_port_id);
		cb->dst_node = le16_to_cpu(v2->dst_node_id);
		cb->dst_port = le16_to_cpu(v2->dst_port_id);

		if (cb->src_port == (u16)QRTR_PORT_CTRL)
			cb->src_port = QRTR_PORT_CTRL;
		if (cb->dst_port == (u16)QRTR_PORT_CTRL)
			cb->dst_port = QRTR_PORT_CTRL;

		size = le32_to_cpu(v2->size);
		break;
	default:
		pr_err("qrtr: Invalid version %d\n", ver);
		goto err;
	}

	if (len != ALIGN(size, 4) + hdrlen)
		goto err;

	if (cb->dst_port != QRTR_PORT_CTRL && cb->type != QRTR_TYPE_DATA)
		goto err;

	skb_put_data(skb, data + hdrlen, size);

	skb_queue_tail(&node->rx_queue, skb);
	schedule_work(&node->work);

	return 0;

err:
	kfree_skb(skb);
	return -EINVAL;

}