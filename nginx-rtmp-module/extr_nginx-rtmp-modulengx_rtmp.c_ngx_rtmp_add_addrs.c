#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {int naddrs; TYPE_5__* addrs; } ;
typedef  TYPE_4__ ngx_rtmp_port_t ;
struct TYPE_13__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {int /*<<< orphan*/  proxy_protocol; TYPE_2__ addr_text; int /*<<< orphan*/  ctx; } ;
struct TYPE_16__ {TYPE_3__ conf; int /*<<< orphan*/  addr; } ;
typedef  TYPE_5__ ngx_rtmp_in_addr_t ;
struct TYPE_17__ {int /*<<< orphan*/  proxy_protocol; scalar_t__ sockaddr; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_6__ ngx_rtmp_conf_addr_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_18__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int NGX_SOCKADDR_STRLEN ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 size_t ngx_sock_ntop (scalar_t__,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_add_addrs(ngx_conf_t *cf, ngx_rtmp_port_t *mport,
    ngx_rtmp_conf_addr_t *addr)
{
    u_char              *p;
    size_t               len;
    ngx_uint_t           i;
    ngx_rtmp_in_addr_t  *addrs;
    struct sockaddr_in  *sin;
    u_char               buf[NGX_SOCKADDR_STRLEN];

    mport->addrs = ngx_pcalloc(cf->pool,
                               mport->naddrs * sizeof(ngx_rtmp_in_addr_t));
    if (mport->addrs == NULL) {
        return NGX_ERROR;
    }

    addrs = mport->addrs;

    for (i = 0; i < mport->naddrs; i++) {

        sin = (struct sockaddr_in *) addr[i].sockaddr;
        addrs[i].addr = sin->sin_addr.s_addr;

        addrs[i].conf.ctx = addr[i].ctx;

        len = ngx_sock_ntop(addr[i].sockaddr,
#if (nginx_version >= 1005003)
                            addr[i].socklen,
#endif
                            buf, NGX_SOCKADDR_STRLEN, 1);

        p = ngx_pnalloc(cf->pool, len);
        if (p == NULL) {
            return NGX_ERROR;
        }

        ngx_memcpy(p, buf, len);

        addrs[i].conf.addr_text.len = len;
        addrs[i].conf.addr_text.data = p;
        addrs[i].conf.proxy_protocol = addr->proxy_protocol;
    }

    return NGX_OK;
}