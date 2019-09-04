#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* connection; scalar_t__ auto_pushed; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_19__ {int /*<<< orphan*/  path; int /*<<< orphan*/  recorder; } ;
typedef  TYPE_4__ ngx_rtmp_record_done_t ;
struct TYPE_20__ {TYPE_2__** url; } ;
typedef  TYPE_5__ ngx_rtmp_notify_app_conf_t ;
struct TYPE_21__ {TYPE_4__* arg; int /*<<< orphan*/  create; TYPE_2__* url; } ;
typedef  TYPE_6__ ngx_rtmp_netcall_init_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ci ;
struct TYPE_17__ {int /*<<< orphan*/  url; } ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 size_t NGX_RTMP_NOTIFY_RECORD_DONE ; 
 int /*<<< orphan*/  next_record_done (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 TYPE_5__* ngx_rtmp_get_module_app_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_create (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_rtmp_notify_module ; 
 int /*<<< orphan*/  ngx_rtmp_notify_record_done_create ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_notify_record_done(ngx_rtmp_session_t *s, ngx_rtmp_record_done_t *v)
{
    ngx_rtmp_netcall_init_t         ci;
    ngx_rtmp_notify_app_conf_t     *nacf;

    if (s->auto_pushed) {
        goto next;
    }

    nacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_notify_module);
    if (nacf == NULL || nacf->url[NGX_RTMP_NOTIFY_RECORD_DONE] == NULL) {
        goto next;
    }

    ngx_log_error(NGX_LOG_INFO, s->connection->log, 0,
                  "notify: record_done recorder=%V path='%V' url='%V'",
                  &v->recorder, &v->path,
                  &nacf->url[NGX_RTMP_NOTIFY_RECORD_DONE]->url);

    ngx_memzero(&ci, sizeof(ci));

    ci.url    = nacf->url[NGX_RTMP_NOTIFY_RECORD_DONE];
    ci.create = ngx_rtmp_notify_record_done_create;
    ci.arg    = v;

    ngx_rtmp_netcall_create(s, &ci);

next:
    return next_record_done(s, v);
}