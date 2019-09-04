#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* sentinel; TYPE_3__* root; } ;
struct TYPE_7__ {TYPE_1__ addr_rbtree; } ;
typedef  TYPE_2__ ngx_resolver_t ;
typedef  int /*<<< orphan*/  ngx_resolver_node_t ;
struct TYPE_8__ {scalar_t__ key; struct TYPE_8__* right; struct TYPE_8__* left; } ;
typedef  TYPE_3__ ngx_rbtree_node_t ;
typedef  scalar_t__ in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_resolver_node (TYPE_3__*) ; 

__attribute__((used)) static ngx_resolver_node_t *
ngx_resolver_lookup_addr(ngx_resolver_t *r, in_addr_t addr)
{
    ngx_rbtree_node_t  *node, *sentinel;

    node = r->addr_rbtree.root;
    sentinel = r->addr_rbtree.sentinel;

    while (node != sentinel) {

        if (addr < node->key) {
            node = node->left;
            continue;
        }

        if (addr > node->key) {
            node = node->right;
            continue;
        }

        /* addr == node->key */

        return ngx_resolver_node(node);
    }

    /* not found */

    return NULL;
}