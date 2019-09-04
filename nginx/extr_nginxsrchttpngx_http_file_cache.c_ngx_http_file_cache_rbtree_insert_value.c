#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ key; struct TYPE_7__* right; struct TYPE_7__* left; struct TYPE_7__* parent; } ;
typedef  TYPE_1__ ngx_rbtree_node_t ;
typedef  int /*<<< orphan*/  ngx_rbtree_key_t ;
struct TYPE_8__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ ngx_http_file_cache_node_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_CACHE_KEY_LEN ; 
 scalar_t__ ngx_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_rbt_red (TYPE_1__*) ; 

__attribute__((used)) static void
ngx_http_file_cache_rbtree_insert_value(ngx_rbtree_node_t *temp,
    ngx_rbtree_node_t *node, ngx_rbtree_node_t *sentinel)
{
    ngx_rbtree_node_t           **p;
    ngx_http_file_cache_node_t   *cn, *cnt;

    for ( ;; ) {

        if (node->key < temp->key) {

            p = &temp->left;

        } else if (node->key > temp->key) {

            p = &temp->right;

        } else { /* node->key == temp->key */

            cn = (ngx_http_file_cache_node_t *) node;
            cnt = (ngx_http_file_cache_node_t *) temp;

            p = (ngx_memcmp(cn->key, cnt->key,
                            NGX_HTTP_CACHE_KEY_LEN - sizeof(ngx_rbtree_key_t))
                 < 0)
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