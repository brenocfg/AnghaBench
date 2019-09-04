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
struct qrtr_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct qrtr_node* qrtr_node_acquire (struct qrtr_node*) ; 
 int /*<<< orphan*/  qrtr_node_lock ; 
 int /*<<< orphan*/  qrtr_nodes ; 
 struct qrtr_node* radix_tree_lookup (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static struct qrtr_node *qrtr_node_lookup(unsigned int nid)
{
	struct qrtr_node *node;

	mutex_lock(&qrtr_node_lock);
	node = radix_tree_lookup(&qrtr_nodes, nid);
	node = qrtr_node_acquire(node);
	mutex_unlock(&qrtr_node_lock);

	return node;
}