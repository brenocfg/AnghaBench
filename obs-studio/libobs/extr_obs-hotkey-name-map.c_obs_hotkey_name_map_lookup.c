#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t num; TYPE_4__* array; } ;
struct TYPE_9__ {int val; TYPE_1__ children; int /*<<< orphan*/  is_leaf; } ;
struct TYPE_8__ {TYPE_3__ root; } ;
typedef  TYPE_2__ obs_hotkey_name_map_t ;
typedef  TYPE_3__ obs_hotkey_name_map_node_t ;
struct TYPE_10__ {size_t prefix_len; TYPE_3__* node; } ;
typedef  TYPE_4__ obs_hotkey_name_map_edge_t ;

/* Variables and functions */
#define  RES_COMMON_PREFIX 131 
#define  RES_MATCHES 130 
#define  RES_NO_MATCH 129 
#define  RES_PREFIX_MATCHES 128 
 int compare_prefix (TYPE_4__*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static bool obs_hotkey_name_map_lookup(obs_hotkey_name_map_t *trie,
				       const char *key, int *v)
{
	if (!trie || !key)
		return false;

	size_t len = strlen(key);
	obs_hotkey_name_map_node_t *n = &trie->root;

	size_t i = 0;
	for (; i < n->children.num;) {
		obs_hotkey_name_map_edge_t *e = &n->children.array[i];

		switch (compare_prefix(e, key, len)) {
		case RES_NO_MATCH:
			i++;
			continue;

		case RES_COMMON_PREFIX:
			return false;

		case RES_PREFIX_MATCHES:
			key += e->prefix_len;
			len -= e->prefix_len;
			n = e->node;
			i = 0;
			continue;

		case RES_MATCHES:
			n = e->node;
			if (!n->is_leaf) {
				for (size_t j = 0; j < n->children.num; j++) {
					if (n->children.array[j].prefix_len)
						continue;

					if (v)
						*v = n->children.array[j]
							     .node->val;
					return true;
				}
				return false;
			}

			if (v)
				*v = n->val;
			return true;
		}
	}

	return false;
}