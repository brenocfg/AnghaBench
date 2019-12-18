#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_31__ {size_t len; } ;
struct TYPE_33__ {size_t hash; int /*<<< orphan*/  value; int /*<<< orphan*/  lowcase_key; TYPE_5__ key; } ;
typedef  TYPE_7__ ngx_table_elt_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_34__ {size_t nelts; TYPE_7__* elts; struct TYPE_34__* next; } ;
typedef  TYPE_8__ ngx_list_part_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_28__ {TYPE_8__ part; } ;
struct TYPE_25__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_29__ {TYPE_2__ headers; TYPE_12__ x_forwarded_for; TYPE_1__* x_real_ip; } ;
struct TYPE_35__ {TYPE_11__* connection; TYPE_3__ headers_in; } ;
typedef  TYPE_9__ ngx_http_request_t ;
struct TYPE_30__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_23__ {int type; size_t hash; int /*<<< orphan*/  recursive; int /*<<< orphan*/ * from; TYPE_4__ header; } ;
typedef  TYPE_10__ ngx_http_realip_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_realip_ctx_t ;
struct TYPE_24__ {TYPE_6__* proxy_protocol; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_11__ ngx_connection_t ;
typedef  TYPE_12__ ngx_array_t ;
struct TYPE_26__ {int /*<<< orphan*/  sockaddr; int /*<<< orphan*/  socklen; } ;
typedef  TYPE_13__ ngx_addr_t ;
struct TYPE_32__ {int /*<<< orphan*/  src_port; int /*<<< orphan*/  src_addr; } ;
struct TYPE_27__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
#define  NGX_HTTP_REALIP_PROXY 130 
#define  NGX_HTTP_REALIP_XFWD 129 
#define  NGX_HTTP_REALIP_XREALIP 128 
 scalar_t__ ngx_http_get_forwarded_addr (TYPE_9__*,TYPE_13__*,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_10__* ngx_http_get_module_loc_conf (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_realip_get_module_ctx (TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_http_realip_module ; 
 scalar_t__ ngx_http_realip_set_addr (TYPE_9__*,TYPE_13__*) ; 
 int /*<<< orphan*/  ngx_inet_set_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_strncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ngx_int_t
ngx_http_realip_handler(ngx_http_request_t *r)
{
    u_char                      *p;
    size_t                       len;
    ngx_str_t                   *value;
    ngx_uint_t                   i, hash;
    ngx_addr_t                   addr;
    ngx_array_t                 *xfwd;
    ngx_list_part_t             *part;
    ngx_table_elt_t             *header;
    ngx_connection_t            *c;
    ngx_http_realip_ctx_t       *ctx;
    ngx_http_realip_loc_conf_t  *rlcf;

    rlcf = ngx_http_get_module_loc_conf(r, ngx_http_realip_module);

    if (rlcf->from == NULL) {
        return NGX_DECLINED;
    }

    ctx = ngx_http_realip_get_module_ctx(r);

    if (ctx) {
        return NGX_DECLINED;
    }

    switch (rlcf->type) {

    case NGX_HTTP_REALIP_XREALIP:

        if (r->headers_in.x_real_ip == NULL) {
            return NGX_DECLINED;
        }

        value = &r->headers_in.x_real_ip->value;
        xfwd = NULL;

        break;

    case NGX_HTTP_REALIP_XFWD:

        xfwd = &r->headers_in.x_forwarded_for;

        if (xfwd->elts == NULL) {
            return NGX_DECLINED;
        }

        value = NULL;

        break;

    case NGX_HTTP_REALIP_PROXY:

        if (r->connection->proxy_protocol == NULL) {
            return NGX_DECLINED;
        }

        value = &r->connection->proxy_protocol->src_addr;
        xfwd = NULL;

        break;

    default: /* NGX_HTTP_REALIP_HEADER */

        part = &r->headers_in.headers.part;
        header = part->elts;

        hash = rlcf->hash;
        len = rlcf->header.len;
        p = rlcf->header.data;

        for (i = 0; /* void */ ; i++) {

            if (i >= part->nelts) {
                if (part->next == NULL) {
                    break;
                }

                part = part->next;
                header = part->elts;
                i = 0;
            }

            if (hash == header[i].hash
                && len == header[i].key.len
                && ngx_strncmp(p, header[i].lowcase_key, len) == 0)
            {
                value = &header[i].value;
                xfwd = NULL;

                goto found;
            }
        }

        return NGX_DECLINED;
    }

found:

    c = r->connection;

    addr.sockaddr = c->sockaddr;
    addr.socklen = c->socklen;
    /* addr.name = c->addr_text; */

    if (ngx_http_get_forwarded_addr(r, &addr, xfwd, value, rlcf->from,
                                    rlcf->recursive)
        != NGX_DECLINED)
    {
        if (rlcf->type == NGX_HTTP_REALIP_PROXY) {
            ngx_inet_set_port(addr.sockaddr, c->proxy_protocol->src_port);
        }

        return ngx_http_realip_set_addr(r, &addr);
    }

    return NGX_DECLINED;
}