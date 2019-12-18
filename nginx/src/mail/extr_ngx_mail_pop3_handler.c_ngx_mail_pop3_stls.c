#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ starttls; } ;
typedef  TYPE_2__ ngx_mail_ssl_conf_t ;
typedef  int /*<<< orphan*/  ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {TYPE_1__* read; int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_6__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_MAIL_PARSE_INVALID_COMMAND ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_mail_get_module_srv_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_ssl_module ; 
 int /*<<< orphan*/  ngx_mail_starttls_handler ; 

__attribute__((used)) static ngx_int_t
ngx_mail_pop3_stls(ngx_mail_session_t *s, ngx_connection_t *c)
{
#if (NGX_MAIL_SSL)
    ngx_mail_ssl_conf_t  *sslcf;

    if (c->ssl == NULL) {
        sslcf = ngx_mail_get_module_srv_conf(s, ngx_mail_ssl_module);
        if (sslcf->starttls) {
            c->read->handler = ngx_mail_starttls_handler;
            return NGX_OK;
        }
    }

#endif

    return NGX_MAIL_PARSE_INVALID_COMMAND;
}