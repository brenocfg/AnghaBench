#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_11__ {int /*<<< orphan*/  mail_state; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  args; } ;
typedef  TYPE_2__ ngx_mail_session_t ;
struct TYPE_12__ {scalar_t__ timedout; TYPE_4__* data; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_13__ {int timedout; TYPE_1__* read; int /*<<< orphan*/  pool; TYPE_2__* data; TYPE_9__* log; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_14__ {char* action; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* handler ) (TYPE_3__*) ;} ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ETIMEDOUT ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ ngx_array_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * ngx_create_temp_buf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_mail_pop3_auth_state (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_mail_session_internal_server_error (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_pop3_start ; 

void
ngx_mail_pop3_init_protocol(ngx_event_t *rev)
{
    ngx_connection_t    *c;
    ngx_mail_session_t  *s;

    c = rev->data;

    c->log->action = "in auth state";

    if (rev->timedout) {
        ngx_log_error(NGX_LOG_INFO, c->log, NGX_ETIMEDOUT, "client timed out");
        c->timedout = 1;
        ngx_mail_close_connection(c);
        return;
    }

    s = c->data;

    if (s->buffer == NULL) {
        if (ngx_array_init(&s->args, c->pool, 2, sizeof(ngx_str_t))
            == NGX_ERROR)
        {
            ngx_mail_session_internal_server_error(s);
            return;
        }

        s->buffer = ngx_create_temp_buf(c->pool, 128);
        if (s->buffer == NULL) {
            ngx_mail_session_internal_server_error(s);
            return;
        }
    }

    s->mail_state = ngx_pop3_start;
    c->read->handler = ngx_mail_pop3_auth_state;

    ngx_mail_pop3_auth_state(rev);
}