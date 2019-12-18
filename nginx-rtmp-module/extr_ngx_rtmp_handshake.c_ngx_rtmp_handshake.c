#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hs_stage; int /*<<< orphan*/  hs_buf; TYPE_3__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_9__ {TYPE_4__* read; int /*<<< orphan*/  log; TYPE_1__* write; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* handler ) (TYPE_4__*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 int /*<<< orphan*/  NGX_RTMP_HANDSHAKE_SERVER_RECV_CHALLENGE ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_alloc_handshake_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_rtmp_handshake_recv (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_rtmp_handshake_send ; 

void
ngx_rtmp_handshake(ngx_rtmp_session_t *s)
{
    ngx_connection_t           *c;

    c = s->connection;
    c->read->handler =  ngx_rtmp_handshake_recv;
    c->write->handler = ngx_rtmp_handshake_send;

    ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
            "handshake: start server handshake");

    s->hs_buf = ngx_rtmp_alloc_handshake_buffer(s);
    s->hs_stage = NGX_RTMP_HANDSHAKE_SERVER_RECV_CHALLENGE;

    ngx_rtmp_handshake_recv(c->read);
}