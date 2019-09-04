#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_18__ {int auth_methods; } ;
typedef  TYPE_4__ ngx_mail_smtp_srv_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_15__ {int nelts; TYPE_3__* elts; } ;
struct TYPE_19__ {int /*<<< orphan*/  out; TYPE_13__ smtp_from; TYPE_2__ cmd; TYPE_1__ args; } ;
typedef  TYPE_5__ ngx_mail_session_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_20__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_MAIL ; 
 int NGX_MAIL_AUTH_NONE_ENABLED ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_13__*) ; 
 TYPE_4__* ngx_mail_get_module_srv_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_smtp_log_rejected_command (TYPE_5__*,TYPE_6__*,char*) ; 
 int /*<<< orphan*/  ngx_mail_smtp_module ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smtp_auth_required ; 
 int /*<<< orphan*/  smtp_bad_sequence ; 
 int /*<<< orphan*/  smtp_invalid_argument ; 
 int /*<<< orphan*/  smtp_ok ; 

__attribute__((used)) static ngx_int_t
ngx_mail_smtp_mail(ngx_mail_session_t *s, ngx_connection_t *c)
{
    ngx_str_t                 *arg, cmd;
    ngx_mail_smtp_srv_conf_t  *sscf;

    sscf = ngx_mail_get_module_srv_conf(s, ngx_mail_smtp_module);

    if (!(sscf->auth_methods & NGX_MAIL_AUTH_NONE_ENABLED)) {
        ngx_mail_smtp_log_rejected_command(s, c, "client was rejected: \"%V\"");
        ngx_str_set(&s->out, smtp_auth_required);
        return NGX_OK;
    }

    /* auth none */

    if (s->smtp_from.len) {
        ngx_str_set(&s->out, smtp_bad_sequence);
        return NGX_OK;
    }

    if (s->args.nelts == 0) {
        ngx_str_set(&s->out, smtp_invalid_argument);
        return NGX_OK;
    }

    arg = s->args.elts;
    arg += s->args.nelts - 1;

    cmd.len = arg->data + arg->len - s->cmd.data;
    cmd.data = s->cmd.data;

    s->smtp_from.len = cmd.len;

    s->smtp_from.data = ngx_pnalloc(c->pool, cmd.len);
    if (s->smtp_from.data == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(s->smtp_from.data, cmd.data, cmd.len);

    ngx_log_debug1(NGX_LOG_DEBUG_MAIL, c->log, 0,
                   "smtp mail from:\"%V\"", &s->smtp_from);

    ngx_str_set(&s->out, smtp_ok);

    return NGX_OK;
}