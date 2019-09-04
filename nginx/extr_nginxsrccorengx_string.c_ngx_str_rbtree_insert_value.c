#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__ str; } ;
typedef  TYPE_2__ ngx_str_node_t ;
struct TYPE_10__ {scalar_t__ key; struct TYPE_10__* right; struct TYPE_10__* left; struct TYPE_10__* parent; } ;
typedef  TYPE_3__ ngx_rbtree_node_t ;

/* Variables and functions */
 scalar_t__ ngx_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_rbt_red (TYPE_3__*) ; 

void
ngx_str_rbtree_insert_value(ngx_rbtree_node_t *temp,
    ngx_rbtree_node_t *node, ngx_rbtree_node_t *sentinel)
{
    ngx_str_node_t      *n, *t;
    ngx_rbtree_node_t  **p;

    for ( ;; ) {

        n = (ngx_str_node_t *) node;
        t = (ngx_str_node_t *) temp;

        if (node->key != temp->key) {

            p = (node->key < temp->key) ? &temp->left : &temp->right;

        } else if (n->str.len != t->str.len) {

            p = (n->str.len < t->str.len) ? &temp->left : &temp->right;

        } else {
            p = (ngx_memcmp(n->str.data, t->str.data, n->str.len) < 0)
                 ? &temp->left : &temp->right;
        }

        if (*p == sentinel) {
            break;
        }

        temp = *p;
    }

    *p = node;
    node->parent = temp;
    node->left = sentinel;
    node->right = sentinel;
    ngx_rbt_red(node);
}