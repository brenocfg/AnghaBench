#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  (* insert ) (TYPE_2__*,TYPE_2__*,TYPE_2__*) ;TYPE_2__* sentinel; TYPE_2__* root; } ;
typedef  TYPE_1__ ngx_rbtree_t ;
struct TYPE_18__ {struct TYPE_18__* parent; struct TYPE_18__* left; struct TYPE_18__* right; } ;
typedef  TYPE_2__ ngx_rbtree_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_rbt_black (TYPE_2__*) ; 
 scalar_t__ ngx_rbt_is_red (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rbt_red (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rbtree_left_rotate (TYPE_2__**,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rbtree_right_rotate (TYPE_2__**,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 

void
ngx_rbtree_insert(ngx_rbtree_t *tree, ngx_rbtree_node_t *node)
{
    ngx_rbtree_node_t  **root, *temp, *sentinel;

    /* a binary tree insert */

    root = &tree->root;
    sentinel = tree->sentinel;

    if (*root == sentinel) {
        node->parent = NULL;
        node->left = sentinel;
        node->right = sentinel;
        ngx_rbt_black(node);
        *root = node;

        return;
    }

    tree->insert(*root, node, sentinel);

    /* re-balance tree */

    while (node != *root && ngx_rbt_is_red(node->parent)) {

        if (node->parent == node->parent->parent->left) {
            temp = node->parent->parent->right;

            if (ngx_rbt_is_red(temp)) {
                ngx_rbt_black(node->parent);
                ngx_rbt_black(temp);
                ngx_rbt_red(node->parent->parent);
                node = node->parent->parent;

            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    ngx_rbtree_left_rotate(root, sentinel, node);
                }

                ngx_rbt_black(node->parent);
                ngx_rbt_red(node->parent->parent);
                ngx_rbtree_right_rotate(root, sentinel, node->parent->parent);
            }

        } else {
            temp = node->parent->parent->left;

            if (ngx_rbt_is_red(temp)) {
                ngx_rbt_black(node->parent);
                ngx_rbt_black(temp);
                ngx_rbt_red(node->parent->parent);
                node = node->parent->parent;

            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    ngx_rbtree_right_rotate(root, sentinel, node);
                }

                ngx_rbt_black(node->parent);
                ngx_rbt_red(node->parent->parent);
                ngx_rbtree_left_rotate(root, sentinel, node->parent->parent);
            }
        }
    }

    ngx_rbt_black(*root);
}