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
struct qrtr_node {int /*<<< orphan*/  item; struct qrtr_endpoint* ep; int /*<<< orphan*/  nid; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  ep_lock; int /*<<< orphan*/  ref; int /*<<< orphan*/  work; } ;
struct qrtr_endpoint {struct qrtr_node* node; int /*<<< orphan*/  xmit; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QRTR_EP_NID_AUTO ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct qrtr_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qrtr_all_nodes ; 
 int /*<<< orphan*/  qrtr_node_assign (struct qrtr_node*,unsigned int) ; 
 int /*<<< orphan*/  qrtr_node_lock ; 
 int /*<<< orphan*/  qrtr_node_rx_work ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

int qrtr_endpoint_register(struct qrtr_endpoint *ep, unsigned int nid)
{
	struct qrtr_node *node;

	if (!ep || !ep->xmit)
		return -EINVAL;

	node = kzalloc(sizeof(*node), GFP_KERNEL);
	if (!node)
		return -ENOMEM;

	INIT_WORK(&node->work, qrtr_node_rx_work);
	kref_init(&node->ref);
	mutex_init(&node->ep_lock);
	skb_queue_head_init(&node->rx_queue);
	node->nid = QRTR_EP_NID_AUTO;
	node->ep = ep;

	qrtr_node_assign(node, nid);

	mutex_lock(&qrtr_node_lock);
	list_add(&node->item, &qrtr_all_nodes);
	mutex_unlock(&qrtr_node_lock);
	ep->node = node;

	return 0;
}