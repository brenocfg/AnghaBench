#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_5__* connection; } ;
typedef  TYPE_3__ ngx_stream_session_t ;
struct TYPE_16__ {int /*<<< orphan*/ * from; } ;
typedef  TYPE_4__ ngx_stream_realip_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {TYPE_2__* proxy_protocol; int /*<<< orphan*/  pool; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_18__ {int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_6__ ngx_addr_t ;
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_14__ {int /*<<< orphan*/  src_port; TYPE_1__ src_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_cidr_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_inet_set_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_parse_addr (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ngx_stream_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_stream_realip_module ; 
 int /*<<< orphan*/  ngx_stream_realip_set_addr (TYPE_3__*,TYPE_6__*) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_realip_handler(ngx_stream_session_t *s)
{
    ngx_addr_t                     addr;
    ngx_connection_t              *c;
    ngx_stream_realip_srv_conf_t  *rscf;

    rscf = ngx_stream_get_module_srv_conf(s, ngx_stream_realip_module);

    if (rscf->from == NULL) {
        return NGX_DECLINED;
    }

    c = s->connection;

    if (c->proxy_protocol == NULL) {
        return NGX_DECLINED;
    }

    if (ngx_cidr_match(c->sockaddr, rscf->from) != NGX_OK) {
        return NGX_DECLINED;
    }

    if (ngx_parse_addr(c->pool, &addr, c->proxy_protocol->src_addr.data,
                       c->proxy_protocol->src_addr.len)
        != NGX_OK)
    {
        return NGX_DECLINED;
    }

    ngx_inet_set_port(addr.sockaddr, c->proxy_protocol->src_port);

    return ngx_stream_realip_set_addr(s, &addr);
}