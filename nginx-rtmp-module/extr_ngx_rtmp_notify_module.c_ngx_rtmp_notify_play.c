#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_2__ ngx_url_t ;
struct TYPE_19__ {TYPE_1__* connection; scalar_t__ auto_pushed; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_20__ {int /*<<< orphan*/  args; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ ngx_rtmp_play_t ;
struct TYPE_21__ {TYPE_2__** url; } ;
typedef  TYPE_5__ ngx_rtmp_notify_app_conf_t ;
struct TYPE_22__ {int argsize; TYPE_4__* arg; int /*<<< orphan*/  handle; int /*<<< orphan*/  create; TYPE_2__* url; } ;
typedef  TYPE_6__ ngx_rtmp_netcall_init_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ci ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 size_t NGX_RTMP_NOTIFY_PLAY ; 
 int /*<<< orphan*/  NGX_RTMP_NOTIFY_PLAYING ; 
 int /*<<< orphan*/  next_play (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 TYPE_5__* ngx_rtmp_get_module_app_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_create (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_rtmp_notify_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_notify_module ; 
 int /*<<< orphan*/  ngx_rtmp_notify_play_create ; 
 int /*<<< orphan*/  ngx_rtmp_notify_play_handle ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_notify_play(ngx_rtmp_session_t *s, ngx_rtmp_play_t *v)
{
    ngx_rtmp_notify_app_conf_t     *nacf;
    ngx_rtmp_netcall_init_t         ci;
    ngx_url_t                      *url;

    if (s->auto_pushed) {
        goto next;
    }

    nacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_notify_module);
    if (nacf == NULL) {
        goto next;
    }

    url = nacf->url[NGX_RTMP_NOTIFY_PLAY];

    ngx_rtmp_notify_init(s, v->name, v->args, NGX_RTMP_NOTIFY_PLAYING);

    if (url == NULL) {
        goto next;
    }

    ngx_log_error(NGX_LOG_INFO, s->connection->log, 0,
                  "notify: play '%V'", &url->url);

    ngx_memzero(&ci, sizeof(ci));

    ci.url = url;
    ci.create = ngx_rtmp_notify_play_create;
    ci.handle = ngx_rtmp_notify_play_handle;
    ci.arg = v;
    ci.argsize = sizeof(*v);

    return ngx_rtmp_netcall_create(s, &ci);

next:
    return next_play(s, v);
}