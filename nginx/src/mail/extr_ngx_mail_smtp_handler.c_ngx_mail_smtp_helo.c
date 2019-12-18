#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_14__ {scalar_t__ starttls; } ;
typedef  TYPE_4__ ngx_mail_ssl_conf_t ;
struct TYPE_15__ {int /*<<< orphan*/  capability; int /*<<< orphan*/  starttls_only_capability; int /*<<< orphan*/  starttls_capability; int /*<<< orphan*/  server_name; } ;
typedef  TYPE_5__ ngx_mail_smtp_srv_conf_t ;
struct TYPE_12__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct TYPE_11__ {int nelts; TYPE_3__* elts; } ;
struct TYPE_16__ {scalar_t__ command; int esmtp; int /*<<< orphan*/  out; int /*<<< orphan*/  smtp_to; int /*<<< orphan*/  smtp_from; TYPE_2__ smtp_helo; TYPE_1__ args; scalar_t__ state; } ;
typedef  TYPE_6__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_17__ {int /*<<< orphan*/ * ssl; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_MAIL_STARTTLS_ON ; 
 scalar_t__ NGX_MAIL_STARTTLS_ONLY ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ NGX_SMTP_HELO ; 
 void* ngx_mail_get_module_srv_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_smtp_module ; 
 int /*<<< orphan*/  ngx_mail_ssl_module ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smtp_invalid_argument ; 

__attribute__((used)) static ngx_int_t
ngx_mail_smtp_helo(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_str_t                 *arg;
    ngx_mail_smtp_srv_conf_t  *sscf;

    if (s->args.nelts != 1) {
        ngx_str_set(&s->out, smtp_invalid_argument);
        s->state = 0;
        return NGX_OK;
    }

    arg = s->args.elts;

    s->smtp_helo.len = arg[0].len;

    s->smtp_helo.data = ngx_pnalloc(c->pool, arg[0].len);
    if (s->smtp_helo.data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(s->smtp_helo.data, arg[0].data, arg[0].len);

    ngx_str_null(&s->smtp_from);
    ngx_str_null(&s->smtp_to);

    sscf = ngx_mail_get_module_srv_conf(s, ngx_mail_smtp_module);

    if (s->command == NGX_SMTP_HELO) {
        s->out = sscf->server_name;

    } else {
        s->esmtp = 1;

#if (NGX_MAIL_SSL)

        if (c->ssl == NULL) {
            ngx_mail_ssl_conf_t  *sslcf;

            sslcf = ngx_mail_get_module_srv_conf(s, ngx_mail_ssl_module);

            if (sslcf->starttls == NGX_MAIL_STARTTLS_ON) {
                s->out = sscf->starttls_capability;
                return NGX_OK;
            }

            if (sslcf->starttls == NGX_MAIL_STARTTLS_ONLY) {
                s->out = sscf->starttls_only_capability;
                return NGX_OK;
            }
        }
#endif

        s->out = sscf->capability;
    }

    return NGX_OK;
}