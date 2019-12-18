#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ len; } ;
struct TYPE_13__ {int quit; TYPE_3__* connection; TYPE_1__ out; TYPE_2__* proxy; } ;
typedef  TYPE_5__ ngx_mail_session_t ;
struct TYPE_14__ {int /*<<< orphan*/  fd; } ;
struct TYPE_12__ {TYPE_8__* connection; } ;
struct TYPE_11__ {int /*<<< orphan*/  write; int /*<<< orphan*/  log; } ;
struct TYPE_10__ {TYPE_4__ upstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  ngx_close_connection (TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_session_internal_server_error (TYPE_5__*) ; 

__attribute__((used)) static void
ngx_mail_proxy_upstream_error(ngx_mail_session_t *s)
{
    if (s->proxy->upstream.connection) {
        ngx_log_debug1(NGX_LOG_DEBUG_MAIL, s->connection->log, 0,
                       "close mail proxy connection: %d",
                       s->proxy->upstream.connection->fd);

        ngx_close_connection(s->proxy->upstream.connection);
    }

    if (s->out.len == 0) {
        ngx_mail_session_internal_server_error(s);
        return;
    }

    s->quit = 1;
    ngx_mail_send(s->connection->write);
}