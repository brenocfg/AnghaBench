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
struct lwan_trie_node {scalar_t__ ref_count; struct lwan_trie_node** next; struct lwan_trie_node* key; int /*<<< orphan*/  data; struct lwan_trie_node* leaf; } ;
struct lwan_trie_leaf {scalar_t__ ref_count; struct lwan_trie_leaf** next; struct lwan_trie_leaf* key; int /*<<< orphan*/  data; struct lwan_trie_leaf* leaf; } ;
struct lwan_trie {int /*<<< orphan*/  (* free_node ) (int /*<<< orphan*/ ) ;} ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct lwan_trie_node*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lwan_trie_node_destroy(struct lwan_trie *trie,
                                   struct lwan_trie_node *node)
{
    if (!node)
        return;

    int32_t nodes_destroyed = node->ref_count;

    for (struct lwan_trie_leaf *leaf = node->leaf; leaf;) {
        struct lwan_trie_leaf *tmp = leaf->next;

        if (trie->free_node)
            trie->free_node(leaf->data);

        free(leaf->key);
        free(leaf);
        leaf = tmp;
    }

    for (int32_t i = 0; nodes_destroyed > 0 && i < 8; i++) {
        if (node->next[i]) {
            lwan_trie_node_destroy(trie, node->next[i]);
            --nodes_destroyed;
        }
    }

    free(node);
}