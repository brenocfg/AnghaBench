#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_msec_t ;
struct TYPE_12__ {int /*<<< orphan*/  greeting; scalar_t__ greeting_delay; } ;
typedef  TYPE_1__ ngx_mail_smtp_srv_conf_t ;
struct TYPE_13__ {int /*<<< orphan*/  out; int /*<<< orphan*/  host; } ;
typedef  TYPE_2__ ngx_mail_session_t ;
struct TYPE_14__ {scalar_t__ timeout; } ;
typedef  TYPE_3__ ngx_mail_core_srv_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  write; TYPE_5__* read; int /*<<< orphan*/  log; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_16__ {int /*<<< orphan*/  handler; scalar_t__ ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_5__*,scalar_t__) ; 
 scalar_t__ ngx_handle_read_event (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 void* ngx_mail_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_smtp_init_protocol ; 
 int /*<<< orphan*/  ngx_mail_smtp_invalid_pipelining ; 
 int /*<<< orphan*/  ngx_mail_smtp_module ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_events ; 

__attribute__((used)) static void
ngx_mail_smtp_greeting(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_msec_t                 timeout;
    ngx_mail_core_srv_conf_t  *cscf;
    ngx_mail_smtp_srv_conf_t  *sscf;

    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "smtp greeting for \"%V\"", &s->host);

    cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);
    sscf = ngx_mail_get_module_srv_conf(s, ngx_mail_smtp_module);

    timeout = sscf->greeting_delay ? sscf->greeting_delay : cscf->timeout;
    ngx_add_timer(c->read, timeout);

    if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
        ngx_mail_close_connection(c);
    }

    if (c->read->ready) {
        ngx_post_event(c->read, &ngx_posted_events);
    }

    if (sscf->greeting_delay) {
         c->read->handler = ngx_mail_smtp_invalid_pipelining;
         return;
    }

    c->read->handler = ngx_mail_smtp_init_protocol;

    s->out = sscf->greeting;

    ngx_mail_send(c->write);
}