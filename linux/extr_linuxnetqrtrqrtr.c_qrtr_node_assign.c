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
struct qrtr_node {unsigned int nid; } ;

/* Variables and functions */
 unsigned int QRTR_EP_NID_AUTO ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qrtr_node_lock ; 
 int /*<<< orphan*/  qrtr_nodes ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,unsigned int,struct qrtr_node*) ; 

__attribute__((used)) static void qrtr_node_assign(struct qrtr_node *node, unsigned int nid)
{
	if (node->nid != QRTR_EP_NID_AUTO || nid == QRTR_EP_NID_AUTO)
		return;

	mutex_lock(&qrtr_node_lock);
	radix_tree_insert(&qrtr_nodes, nid, node);
	node->nid = nid;
	mutex_unlock(&qrtr_node_lock);
}