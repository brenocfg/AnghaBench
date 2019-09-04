#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_9__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__ str; } ;
typedef  TYPE_3__ ngx_str_node_t ;
struct TYPE_12__ {TYPE_5__* sentinel; TYPE_5__* root; } ;
typedef  TYPE_4__ ngx_rbtree_t ;
struct TYPE_13__ {scalar_t__ key; struct TYPE_13__* right; struct TYPE_13__* left; } ;
typedef  TYPE_5__ ngx_rbtree_node_t ;
typedef  scalar_t__ ngx_int_t ;

/* Variables and functions */
 scalar_t__ ngx_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

ngx_str_node_t *
ngx_str_rbtree_lookup(ngx_rbtree_t *rbtree, ngx_str_t *val, uint32_t hash)
{
    ngx_int_t           rc;
    ngx_str_node_t     *n;
    ngx_rbtree_node_t  *node, *sentinel;

    node = rbtree->root;
    sentinel = rbtree->sentinel;

    while (node != sentinel) {

        n = (ngx_str_node_t *) node;

        if (hash != node->key) {
            node = (hash < node->key) ? node->left : node->right;
            continue;
        }

        if (val->len != n->str.len) {
            node = (val->len < n->str.len) ? node->left : node->right;
            continue;
        }

        rc = ngx_memcmp(val->data, n->str.data, val->len);

        if (rc < 0) {
            node = node->left;
            continue;
        }

        if (rc > 0) {
            node = node->right;
            continue;
        }

        return n;
    }

    return NULL;
}