#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* connection; } ;
typedef  TYPE_2__ ngx_udp_connection_t ;
struct TYPE_11__ {scalar_t__ key; struct TYPE_11__* right; struct TYPE_11__* left; struct TYPE_11__* parent; } ;
typedef  TYPE_3__ ngx_rbtree_node_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_12__ {int /*<<< orphan*/  local_socklen; int /*<<< orphan*/  local_sockaddr; TYPE_1__* listening; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_9__ {scalar_t__ wildcard; } ;

/* Variables and functions */
 scalar_t__ ngx_cmp_sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_rbt_red (TYPE_3__*) ; 

void
ngx_udp_rbtree_insert_value(ngx_rbtree_node_t *temp,
    ngx_rbtree_node_t *node, ngx_rbtree_node_t *sentinel)
{
    ngx_int_t               rc;
    ngx_connection_t       *c, *ct;
    ngx_rbtree_node_t     **p;
    ngx_udp_connection_t   *udp, *udpt;

    for ( ;; ) {

        if (node->key < temp->key) {

            p = &temp->left;

        } else if (node->key > temp->key) {

            p = &temp->right;

        } else { /* node->key == temp->key */

            udp = (ngx_udp_connection_t *) node;
            c = udp->connection;

            udpt = (ngx_udp_connection_t *) temp;
            ct = udpt->connection;

            rc = ngx_cmp_sockaddr(c->sockaddr, c->socklen,
                                  ct->sockaddr, ct->socklen, 1);

            if (rc == 0 && c->listening->wildcard) {
                rc = ngx_cmp_sockaddr(c->local_sockaddr, c->local_socklen,
                                      ct->local_sockaddr, ct->local_socklen, 1);
            }

            p = (rc < 0) ? &temp->left : &temp->right;
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