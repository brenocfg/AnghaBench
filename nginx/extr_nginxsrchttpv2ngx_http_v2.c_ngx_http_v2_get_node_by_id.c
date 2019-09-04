#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_http_v2_srv_conf_t ;
struct TYPE_12__ {size_t id; struct TYPE_12__* index; int /*<<< orphan*/  children; } ;
typedef  TYPE_3__ ngx_http_v2_node_t ;
struct TYPE_13__ {int closed_nodes; TYPE_3__** streams_index; TYPE_2__* connection; TYPE_1__* http_connection; } ;
typedef  TYPE_4__ ngx_http_v2_connection_t ;
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;
struct TYPE_10__ {int /*<<< orphan*/  conf_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_http_get_module_srv_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_v2_get_closed_node (TYPE_4__*) ; 
 size_t ngx_http_v2_index (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 TYPE_3__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_queue_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_http_v2_node_t *
ngx_http_v2_get_node_by_id(ngx_http_v2_connection_t *h2c, ngx_uint_t sid,
    ngx_uint_t alloc)
{
    ngx_uint_t               index;
    ngx_http_v2_node_t      *node;
    ngx_http_v2_srv_conf_t  *h2scf;

    h2scf = ngx_http_get_module_srv_conf(h2c->http_connection->conf_ctx,
                                         ngx_http_v2_module);

    index = ngx_http_v2_index(h2scf, sid);

    for (node = h2c->streams_index[index]; node; node = node->index) {

        if (node->id == sid) {
            return node;
        }
    }

    if (!alloc) {
        return NULL;
    }

    if (h2c->closed_nodes < 32) {
        node = ngx_pcalloc(h2c->connection->pool, sizeof(ngx_http_v2_node_t));
        if (node == NULL) {
            return NULL;
        }

    } else {
        node = ngx_http_v2_get_closed_node(h2c);
    }

    node->id = sid;

    ngx_queue_init(&node->children);

    node->index = h2c->streams_index[index];
    h2c->streams_index[index] = node;

    return node;
}