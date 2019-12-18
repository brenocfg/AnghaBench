#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_20__ {size_t type; int /*<<< orphan*/  msid; int /*<<< orphan*/  mlen; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  csid; } ;
typedef  TYPE_3__ ngx_rtmp_header_t ;
typedef  int (* ngx_rtmp_handler_pt ) (TYPE_2__*,TYPE_3__*,TYPE_6__*) ;
struct TYPE_22__ {TYPE_9__* events; } ;
typedef  TYPE_7__ ngx_rtmp_core_main_conf_t ;
typedef  int const ngx_int_t ;
struct TYPE_21__ {struct TYPE_21__* next; } ;
typedef  TYPE_6__ ngx_chain_t ;
struct TYPE_23__ {int (* elts ) (TYPE_2__*,TYPE_3__*,TYPE_6__*) ;size_t nelts; } ;
typedef  TYPE_9__ ngx_array_t ;
struct TYPE_18__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
#define  NGX_DONE 129 
#define  NGX_ERROR 128 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int const NGX_OK ; 
 size_t NGX_RTMP_MSG_MAX ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 TYPE_7__* ngx_rtmp_get_module_main_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_message_type (size_t) ; 
 int stub1 (TYPE_2__*,TYPE_3__*,TYPE_6__*) ; 

ngx_int_t
ngx_rtmp_receive_message(ngx_rtmp_session_t *s,
        ngx_rtmp_header_t *h, ngx_chain_t *in)
{
    ngx_rtmp_core_main_conf_t  *cmcf;
    ngx_array_t                *evhs;
    size_t                      n;
    ngx_rtmp_handler_pt        *evh;

    cmcf = ngx_rtmp_get_module_main_conf(s, ngx_rtmp_core_module);

#ifdef NGX_DEBUG
    {
        int             nbufs;
        ngx_chain_t    *ch;

        for(nbufs = 1, ch = in;
                ch->next;
                ch = ch->next, ++nbufs);

        ngx_log_debug7(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "RTMP recv %s (%d) csid=%D timestamp=%D "
                "mlen=%D msid=%D nbufs=%d",
                ngx_rtmp_message_type(h->type), (int)h->type,
                h->csid, h->timestamp, h->mlen, h->msid, nbufs);
    }
#endif

    if (h->type > NGX_RTMP_MSG_MAX) {
        ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "unexpected RTMP message type: %d", (int)h->type);
        return NGX_OK;
    }

    evhs = &cmcf->events[h->type];
    evh = evhs->elts;

    ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
            "nhandlers: %d", evhs->nelts);

    for(n = 0; n < evhs->nelts; ++n, ++evh) {
        if (!evh) {
            continue;
        }
        ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "calling handler %d", n);

        switch ((*evh)(s, h, in)) {
            case NGX_ERROR:
                ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                        "handler %d failed", n);
                return NGX_ERROR;
            case NGX_DONE:
                return NGX_OK;
        }
    }

    return NGX_OK;
}