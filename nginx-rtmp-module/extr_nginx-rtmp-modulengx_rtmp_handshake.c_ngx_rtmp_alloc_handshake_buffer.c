#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_13__ {int /*<<< orphan*/  pool; TYPE_4__* free_hs; } ;
typedef  TYPE_3__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_14__ {struct TYPE_14__* next; TYPE_5__* buf; } ;
typedef  TYPE_4__ ngx_chain_t ;
struct TYPE_15__ {int memory; int /*<<< orphan*/ * start; int /*<<< orphan*/ * last; int /*<<< orphan*/ * pos; int /*<<< orphan*/ * end; } ;
typedef  TYPE_5__ ngx_buf_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int NGX_RTMP_HANDSHAKE_BUFSIZE ; 
 int /*<<< orphan*/  ngx_free_chain (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 TYPE_3__* ngx_rtmp_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_buf_t *
ngx_rtmp_alloc_handshake_buffer(ngx_rtmp_session_t *s)
{
    ngx_rtmp_core_srv_conf_t   *cscf;
    ngx_chain_t                *cl;
    ngx_buf_t                  *b;

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
            "handshake: allocating buffer");

    cscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_core_module);

    if (cscf->free_hs) {
        cl = cscf->free_hs;
        b = cl->buf;
        cscf->free_hs = cl->next;
        ngx_free_chain(cscf->pool, cl);

    } else {
        b = ngx_pcalloc(cscf->pool, sizeof(ngx_buf_t));
        if (b == NULL) {
            return NULL;
        }
        b->memory = 1;
        b->start = ngx_pcalloc(cscf->pool, NGX_RTMP_HANDSHAKE_BUFSIZE);
        if (b->start == NULL) {
            return NULL;
        }
        b->end = b->start + NGX_RTMP_HANDSHAKE_BUFSIZE;
    }

    b->pos = b->last = b->start;

    return b;
}