#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  handler; int /*<<< orphan*/  log; TYPE_4__* data; } ;
struct TYPE_10__ {TYPE_2__ ping_evt; TYPE_4__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_11__ {TYPE_6__* read; int /*<<< orphan*/  log; TYPE_1__* write; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* handler ) (TYPE_6__*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_rtmp_ping ; 
 int /*<<< orphan*/  ngx_rtmp_recv (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_rtmp_reset_ping (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_rtmp_send ; 

void
ngx_rtmp_cycle(ngx_rtmp_session_t *s)
{
    ngx_connection_t           *c;

    c = s->connection;
    c->read->handler =  ngx_rtmp_recv;
    c->write->handler = ngx_rtmp_send;

    s->ping_evt.data = c;
    s->ping_evt.log = c->log;
    s->ping_evt.handler = ngx_rtmp_ping;
    ngx_rtmp_reset_ping(s);

    ngx_rtmp_recv(c->read);
}