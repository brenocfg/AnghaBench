#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ nelts; } ;
struct TYPE_12__ {int /*<<< orphan*/  mail_state; int /*<<< orphan*/  out; scalar_t__ state; TYPE_1__ args; } ;
typedef  TYPE_2__ ngx_mail_session_t ;
struct TYPE_13__ {int auth_methods; int /*<<< orphan*/  auth_capability; } ;
typedef  TYPE_3__ ngx_mail_pop3_srv_conf_t ;
typedef  int ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_connection_t ;

/* Variables and functions */
 int NGX_ERROR ; 
#define  NGX_MAIL_AUTH_CRAM_MD5 132 
 int NGX_MAIL_AUTH_CRAM_MD5_ENABLED ; 
#define  NGX_MAIL_AUTH_EXTERNAL 131 
 int NGX_MAIL_AUTH_EXTERNAL_ENABLED ; 
#define  NGX_MAIL_AUTH_LOGIN 130 
#define  NGX_MAIL_AUTH_LOGIN_USERNAME 129 
#define  NGX_MAIL_AUTH_PLAIN 128 
 int NGX_MAIL_PARSE_INVALID_COMMAND ; 
 int NGX_OK ; 
 int ngx_mail_auth_cram_md5_salt (TYPE_2__*,int /*<<< orphan*/ *,char*,int) ; 
 int ngx_mail_auth_login_username (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int ngx_mail_auth_parse (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_mail_get_module_srv_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_pop3_module ; 
 scalar_t__ ngx_mail_starttls_only (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_pop3_auth_cram_md5 ; 
 int /*<<< orphan*/  ngx_pop3_auth_external ; 
 int /*<<< orphan*/  ngx_pop3_auth_login_password ; 
 int /*<<< orphan*/  ngx_pop3_auth_login_username ; 
 int /*<<< orphan*/  ngx_pop3_auth_plain ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop3_next ; 
 int /*<<< orphan*/  pop3_password ; 
 int /*<<< orphan*/  pop3_username ; 

__attribute__((used)) static ngx_int_t
ngx_mail_pop3_auth(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_int_t                  rc;
    ngx_mail_pop3_srv_conf_t  *pscf;

#if (NGX_MAIL_SSL)
    if (ngx_mail_starttls_only(s, c)) {
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }
#endif

    pscf = ngx_mail_get_module_srv_conf(s, ngx_mail_pop3_module);

    if (s->args.nelts == 0) {
        s->out = pscf->auth_capability;
        s->state = 0;

        return NGX_OK;
    }

    rc = ngx_mail_auth_parse(s, c);

    switch (rc) {

    case NGX_MAIL_AUTH_LOGIN:

        ngx_str_set(&s->out, pop3_username);
        s->mail_state = ngx_pop3_auth_login_username;

        return NGX_OK;

    case NGX_MAIL_AUTH_LOGIN_USERNAME:

        ngx_str_set(&s->out, pop3_password);
        s->mail_state = ngx_pop3_auth_login_password;

        return ngx_mail_auth_login_username(s, c, 1);

    case NGX_MAIL_AUTH_PLAIN:

        ngx_str_set(&s->out, pop3_next);
        s->mail_state = ngx_pop3_auth_plain;

        return NGX_OK;

    case NGX_MAIL_AUTH_CRAM_MD5:

        if (!(pscf->auth_methods & NGX_MAIL_AUTH_CRAM_MD5_ENABLED)) {
            return NGX_MAIL_PARSE_INVALID_COMMAND;
        }

        if (ngx_mail_auth_cram_md5_salt(s, c, "+ ", 2) == NGX_OK) {
            s->mail_state = ngx_pop3_auth_cram_md5;
            return NGX_OK;
        }

        return NGX_ERROR;

    case NGX_MAIL_AUTH_EXTERNAL:

        if (!(pscf->auth_methods & NGX_MAIL_AUTH_EXTERNAL_ENABLED)) {
            return NGX_MAIL_PARSE_INVALID_COMMAND;
        }

        ngx_str_set(&s->out, pop3_username);
        s->mail_state = ngx_pop3_auth_external;

        return NGX_OK;
    }

    return rc;
}