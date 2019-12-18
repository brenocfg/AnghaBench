#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_17__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int nelts; TYPE_2__* elts; } ;
struct TYPE_15__ {TYPE_9__ login; TYPE_10__ passwd; TYPE_1__ args; } ;
typedef  TYPE_3__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_16__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int /*<<< orphan*/  NGX_MAIL_PARSE_INVALID_COMMAND ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_9__*,TYPE_10__*) ; 
 scalar_t__ ngx_mail_starttls_only (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 void* ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_mail_imap_login(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_str_t  *arg;

#if (NGX_MAIL_SSL)
    if (ngx_mail_starttls_only(s, c)) {
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }
#endif

    arg = s->args.elts;

    if (s->args.nelts != 2 || arg[0].len == 0) {
        return NGX_MAIL_PARSE_INVALID_COMMAND;
    }

    s->login.len = arg[0].len;
    s->login.data = ngx_pnalloc(c->pool, s->login.len);
    if (s->login.data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(s->login.data, arg[0].data, s->login.len);

    s->passwd.len = arg[1].len;
    s->passwd.data = ngx_pnalloc(c->pool, s->passwd.len);
    if (s->passwd.data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(s->passwd.data, arg[1].data, s->passwd.len);

#if (NGX_DEBUG_MAIL_PASSWD)
    ngx_log_debug2(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "imap login:\"%V\" passwd:\"%V\"",
                   &s->login, &s->passwd);
#else
    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "imap login:\"%V\"", &s->login);
#endif

    return NGX_DONE;
}