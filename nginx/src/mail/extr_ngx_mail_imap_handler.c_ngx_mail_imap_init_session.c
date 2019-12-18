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
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ ngx_mail_session_t ;
struct TYPE_12__ {int /*<<< orphan*/  timeout; } ;
typedef  TYPE_2__ ngx_mail_core_srv_conf_t ;
struct TYPE_13__ {int /*<<< orphan*/  write; TYPE_9__* read; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_14__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  imap_greeting ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_9__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_handle_read_event (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_close_connection (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 TYPE_2__* ngx_mail_get_module_srv_conf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_imap_init_protocol ; 
 int /*<<< orphan*/  ngx_mail_send (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ngx_mail_imap_init_session(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_mail_core_srv_conf_t  *cscf;

    cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);

    ngx_str_set(&s->out, imap_greeting);

    c->read->handler = ngx_mail_imap_init_protocol;

    ngx_add_timer(c->read, cscf->timeout);

    if (ngx_handle_read_event(c->read, 0) != NGX_OK) {
        ngx_mail_close_connection(c);
    }

    ngx_mail_send(c->write);
}