#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ ngx_mail_session_t ;
struct TYPE_7__ {int /*<<< orphan*/  capability; } ;
typedef  TYPE_2__ ngx_mail_pop3_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_2__* ngx_mail_get_module_srv_conf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_pop3_module ; 

__attribute__((used)) static ngx_int_t
ngx_mail_pop3_capa(ngx_mail_session_t *s, ngx_connection_t *c, ngx_int_t stls)
{
    ngx_mail_pop3_srv_conf_t  *pscf;

    pscf = ngx_mail_get_module_srv_conf(s, ngx_mail_pop3_module);

#if (NGX_MAIL_SSL)

    if (stls && c->ssl == NULL) {
        ngx_mail_ssl_conf_t  *sslcf;

        sslcf = ngx_mail_get_module_srv_conf(s, ngx_mail_ssl_module);

        if (sslcf->starttls == NGX_MAIL_STARTTLS_ON) {
            s->out = pscf->starttls_capability;
            return NGX_OK;
        }

        if (sslcf->starttls == NGX_MAIL_STARTTLS_ONLY) {
            s->out = pscf->starttls_only_capability;
            return NGX_OK;
        }
    }

#endif

    s->out = pscf->capability;
    return NGX_OK;
}