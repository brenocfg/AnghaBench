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
typedef  int /*<<< orphan*/  u8 ;
struct qtnf_sta_list {int /*<<< orphan*/  size; int /*<<< orphan*/  head; } ;
struct qtnf_vif {int /*<<< orphan*/  generation; struct qtnf_sta_list sta_list; } ;
struct qtnf_sta_node {int /*<<< orphan*/  list; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct qtnf_sta_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct qtnf_sta_node* qtnf_sta_list_lookup (struct qtnf_sta_list*,int /*<<< orphan*/  const*) ; 
 scalar_t__ unlikely (int) ; 

struct qtnf_sta_node *qtnf_sta_list_add(struct qtnf_vif *vif,
					const u8 *mac)
{
	struct qtnf_sta_list *list = &vif->sta_list;
	struct qtnf_sta_node *node;

	if (unlikely(!mac))
		return NULL;

	node = qtnf_sta_list_lookup(list, mac);

	if (node)
		goto done;

	node = kzalloc(sizeof(*node), GFP_KERNEL);
	if (unlikely(!node))
		goto done;

	ether_addr_copy(node->mac_addr, mac);
	list_add_tail(&node->list, &list->head);
	atomic_inc(&list->size);
	++vif->generation;

done:
	return node;
}