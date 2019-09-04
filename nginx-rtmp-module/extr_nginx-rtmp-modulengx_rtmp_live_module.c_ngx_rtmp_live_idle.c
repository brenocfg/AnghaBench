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
struct TYPE_8__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_rtmp_session_t ;
struct TYPE_9__ {TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_10__ {TYPE_2__* data; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_rtmp_finalize_session (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_rtmp_live_idle(ngx_event_t *pev)
{
    ngx_connection_t           *c;
    ngx_rtmp_session_t         *s;

    c = pev->data;
    s = c->data;

    ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                  "live: drop idle publisher");

    ngx_rtmp_finalize_session(s);
}