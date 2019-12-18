#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ starttls; } ;
typedef  TYPE_3__ ngx_mail_ssl_conf_t ;
struct TYPE_13__ {TYPE_1__* buffer; int /*<<< orphan*/  smtp_to; int /*<<< orphan*/  smtp_from; int /*<<< orphan*/  smtp_helo; } ;
typedef  TYPE_4__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_14__ {TYPE_2__* read; int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_11__ {int /*<<< orphan*/  handler; } ;
struct TYPE_10__ {int /*<<< orphan*/  start; int /*<<< orphan*/  last; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_MAIL_PARSE_INVALID_COMMAND ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_3__* ngx_mail_get_module_srv_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_ssl_module ; 
 int /*<<< orphan*/  ngx_mail_starttls_handler ; 
 int /*<<< orphan*/  ngx_str_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_mail_smtp_starttls(ngx_mail_session_t *s, ngx_connection_t *c)
{
#if (NGX_MAIL_SSL)
    ngx_mail_ssl_conf_t  *sslcf;

    if (c->ssl == NULL) {
        sslcf = ngx_mail_get_module_srv_conf(s, ngx_mail_ssl_module);
        if (sslcf->starttls) {

            /*
             * RFC3207 requires us to discard any knowledge
             * obtained from client before STARTTLS.
             */

            ngx_str_null(&s->smtp_helo);
            ngx_str_null(&s->smtp_from);
            ngx_str_null(&s->smtp_to);

            s->buffer->pos = s->buffer->start;
            s->buffer->last = s->buffer->start;

            c->read->handler = ngx_mail_starttls_handler;
            return NGX_OK;
        }
    }

#endif

    return NGX_MAIL_PARSE_INVALID_COMMAND;
}