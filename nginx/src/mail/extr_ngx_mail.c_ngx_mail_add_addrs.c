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
struct TYPE_12__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {int naddrs; TYPE_5__* addrs; } ;
typedef  TYPE_4__ ngx_mail_port_t ;
struct TYPE_13__ {int /*<<< orphan*/  addr_text; int /*<<< orphan*/  ssl; int /*<<< orphan*/  ctx; } ;
struct TYPE_16__ {TYPE_2__ conf; int /*<<< orphan*/  addr; } ;
typedef  TYPE_5__ ngx_mail_in_addr_t ;
struct TYPE_14__ {int /*<<< orphan*/  addr_text; int /*<<< orphan*/  ssl; int /*<<< orphan*/  ctx; scalar_t__ sockaddr; } ;
struct TYPE_17__ {TYPE_3__ opt; } ;
typedef  TYPE_6__ ngx_mail_conf_addr_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_18__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_5__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_mail_add_addrs(ngx_conf_t *cf, ngx_mail_port_t *mport,
    ngx_mail_conf_addr_t *addr)
{
    ngx_uint_t           i;
    ngx_mail_in_addr_t  *addrs;
    struct sockaddr_in  *sin;

    mport->addrs = ngx_pcalloc(cf->pool,
                               mport->naddrs * sizeof(ngx_mail_in_addr_t));
    if (mport->addrs == NULL) {
        return NGX_ERROR;
    }

    addrs = mport->addrs;

    for (i = 0; i < mport->naddrs; i++) {

        sin = (struct sockaddr_in *) addr[i].opt.sockaddr;
        addrs[i].addr = sin->sin_addr.s_addr;

        addrs[i].conf.ctx = addr[i].opt.ctx;
#if (NGX_MAIL_SSL)
        addrs[i].conf.ssl = addr[i].opt.ssl;
#endif
        addrs[i].conf.addr_text = addr[i].opt.addr_text;
    }

    return NGX_OK;
}