#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ starttls; } ;
typedef  TYPE_1__ ngx_mail_ssl_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_2__ ngx_mail_session_t ;
struct TYPE_10__ {int /*<<< orphan*/  capability; int /*<<< orphan*/  starttls_only_capability; int /*<<< orphan*/  starttls_capability; } ;
typedef  TYPE_3__ ngx_mail_imap_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_11__ {int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_MAIL_STARTTLS_ON ; 
 scalar_t__ NGX_MAIL_STARTTLS_ONLY ; 
 int /*<<< orphan*/  NGX_OK ; 
 void* ngx_mail_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_imap_module ; 
 int /*<<< orphan*/  ngx_mail_ssl_module ; 

__attribute__((used)) static ngx_int_t
ngx_mail_imap_capability(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_mail_imap_srv_conf_t  *iscf;

    iscf = ngx_mail_get_module_srv_conf(s, ngx_mail_imap_module);

#if (NGX_MAIL_SSL)

    if (c->ssl == NULL) {
        ngx_mail_ssl_conf_t  *sslcf;

        sslcf = ngx_mail_get_module_srv_conf(s, ngx_mail_ssl_module);

        if (sslcf->starttls == NGX_MAIL_STARTTLS_ON) {
            s->text = iscf->starttls_capability;
            return NGX_OK;
        }

        if (sslcf->starttls == NGX_MAIL_STARTTLS_ONLY) {
            s->text = iscf->starttls_only_capability;
            return NGX_OK;
        }
    }
#endif

    s->text = iscf->capability;

    return NGX_OK;
}