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
struct batadv_priv {int /*<<< orphan*/  orig_hash; } ;
struct batadv_orig_node {int /*<<< orphan*/  hash_entry; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_choose_orig ; 
 int /*<<< orphan*/  batadv_compare_orig ; 
 int batadv_hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct batadv_orig_node*,int /*<<< orphan*/ *) ; 
 struct batadv_orig_node* batadv_orig_hash_find (struct batadv_priv*,int /*<<< orphan*/  const*) ; 
 struct batadv_orig_node* batadv_orig_node_new (struct batadv_priv*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 

struct batadv_orig_node *batadv_v_ogm_orig_get(struct batadv_priv *bat_priv,
					       const u8 *addr)
{
	struct batadv_orig_node *orig_node;
	int hash_added;

	orig_node = batadv_orig_hash_find(bat_priv, addr);
	if (orig_node)
		return orig_node;

	orig_node = batadv_orig_node_new(bat_priv, addr);
	if (!orig_node)
		return NULL;

	kref_get(&orig_node->refcount);
	hash_added = batadv_hash_add(bat_priv->orig_hash, batadv_compare_orig,
				     batadv_choose_orig, orig_node,
				     &orig_node->hash_entry);
	if (hash_added != 0) {
		/* remove refcnt for newly created orig_node and hash entry */
		batadv_orig_node_put(orig_node);
		batadv_orig_node_put(orig_node);
		orig_node = NULL;
	}

	return orig_node;
}