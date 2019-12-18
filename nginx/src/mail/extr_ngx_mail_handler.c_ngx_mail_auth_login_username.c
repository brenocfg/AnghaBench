#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_10__ {TYPE_2__* elts; } ;
struct TYPE_12__ {TYPE_2__ login; TYPE_1__ args; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_13__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_MAIL_PARSE_INVALID_COMMAND ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_base64_decoded_length (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_decode_base64 (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_mail_auth_login_username(ngx_mail_session_t *s, ngx_connection_t *c,
    ngx_uint_t n)
{
    ngx_str_t  *arg;

    arg = s->args.elts;

    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "mail auth login username: \"%V\"", &arg[n]);

    s->login.data = ngx_pnalloc(c->pool, ngx_base64_decoded_length(arg[n].len));
    if (s->login.data == NULL) {
        return NGX_ERROR;
    }

    if (ngx_decode_base64(&s->login, &arg[n]) != NGX_OK) {
        ngx_log_error(NGX_LOG_INFO, c->log, 0,
            "client sent invalid base64 encoding in AUTH LOGIN command");
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "mail auth login username: \"%V\"", &s->login);

    return NGX_OK;
}