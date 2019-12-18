#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t num; TYPE_2__* array; } ;
struct TYPE_13__ {int val; TYPE_8__ children; scalar_t__ is_leaf; } ;
typedef  TYPE_1__ obs_hotkey_name_map_node_t ;
struct TYPE_14__ {int /*<<< orphan*/  prefix_len; TYPE_1__* node; } ;
typedef  TYPE_2__ obs_hotkey_name_map_edge_t ;

/* Variables and functions */
#define  RES_COMMON_PREFIX 131 
#define  RES_MATCHES 130 
#define  RES_NO_MATCH 129 
#define  RES_PREFIX_MATCHES 128 
 int /*<<< orphan*/  add_leaf (TYPE_1__*,char const*,size_t,int) ; 
 int compare_prefix (TYPE_2__*,char const*,size_t) ; 
 int /*<<< orphan*/  connect (TYPE_2__*,TYPE_1__*) ; 
 TYPE_2__* da_push_back_new (TYPE_8__) ; 
 TYPE_1__* new_node () ; 
 int /*<<< orphan*/  reduce_edge (TYPE_2__*,char const*,size_t,int) ; 

__attribute__((used)) static void insert(obs_hotkey_name_map_edge_t *edge,
		   obs_hotkey_name_map_node_t *node, const char *key, size_t l,
		   int v)
{
	if (node->is_leaf && l > 0) {
		obs_hotkey_name_map_node_t *new_node_ = new_node();
		connect(edge, new_node_);

		obs_hotkey_name_map_edge_t *edge =
			da_push_back_new(new_node_->children);
		connect(edge, node);
		add_leaf(new_node_, key, l, v);
		return;
	}

	if (node->is_leaf && l == 0) {
		node->val = v;
		return;
	}

	for (size_t i = 0; i < node->children.num; i++) {
		obs_hotkey_name_map_edge_t *e = &node->children.array[i];

		switch (compare_prefix(e, key, l)) {
		case RES_NO_MATCH:
			continue;

		case RES_MATCHES:
		case RES_PREFIX_MATCHES:
			insert(e, e->node, key + e->prefix_len,
			       l - e->prefix_len, v);
			return;

		case RES_COMMON_PREFIX:
			reduce_edge(e, key, l, v);
			return;
		}
	}

	add_leaf(node, key, l, v);
}