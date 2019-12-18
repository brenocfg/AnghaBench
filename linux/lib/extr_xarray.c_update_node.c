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
struct xa_state {int dummy; } ;
struct xa_node {scalar_t__ count; scalar_t__ nr_values; } ;

/* Variables and functions */
 scalar_t__ XA_CHUNK_SIZE ; 
 int /*<<< orphan*/  XA_NODE_BUG_ON (struct xa_node*,int) ; 
 int /*<<< orphan*/  xas_delete_node (struct xa_state*) ; 
 int /*<<< orphan*/  xas_update (struct xa_state*,struct xa_node*) ; 

__attribute__((used)) static void update_node(struct xa_state *xas, struct xa_node *node,
		int count, int values)
{
	if (!node || (!count && !values))
		return;

	node->count += count;
	node->nr_values += values;
	XA_NODE_BUG_ON(node, node->count > XA_CHUNK_SIZE);
	XA_NODE_BUG_ON(node, node->nr_values > XA_CHUNK_SIZE);
	xas_update(xas, node);
	if (count < 0)
		xas_delete_node(xas);
}