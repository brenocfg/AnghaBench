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
struct TYPE_8__ {int /*<<< orphan*/ * hs_buf; } ;
typedef  TYPE_1__ ngx_rtmp_session_t ;
struct TYPE_9__ {TYPE_3__* free_hs; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_10__ {struct TYPE_10__* next; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_3__ ngx_chain_t ;

/* Variables and functions */
 TYPE_3__* ngx_alloc_chain_link (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 TYPE_2__* ngx_rtmp_get_module_srv_conf (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
ngx_rtmp_free_handshake_buffers(ngx_rtmp_session_t *s)
{
    ngx_rtmp_core_srv_conf_t   *cscf;
    ngx_chain_t                *cl;

    if (s->hs_buf == NULL) {
        return;
    }
    cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);
    cl = ngx_alloc_chain_link(cscf->pool);
    if (cl == NULL) {
        return;
    }
    cl->buf = s->hs_buf;
    cl->next = cscf->free_hs;
    cscf->free_hs = cl;
    s->hs_buf = NULL;
}