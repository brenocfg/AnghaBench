#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_2__ ngx_url_t ;
struct TYPE_15__ {TYPE_1__* connection; scalar_t__ relay; scalar_t__ auto_pushed; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_16__ {TYPE_2__** url; } ;
typedef  TYPE_4__ ngx_rtmp_notify_srv_conf_t ;
struct TYPE_17__ {int /*<<< orphan*/  create; TYPE_2__* url; } ;
typedef  TYPE_5__ ngx_rtmp_netcall_init_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ci ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 size_t NGX_RTMP_NOTIFY_DISCONNECT ; 
 int /*<<< orphan*/  next_disconnect (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 TYPE_4__* ngx_rtmp_get_module_srv_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_create (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_rtmp_notify_disconnect_create ; 
 int /*<<< orphan*/  ngx_rtmp_notify_module ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_notify_disconnect(ngx_rtmp_session_t *s)
{
    ngx_rtmp_notify_srv_conf_t     *nscf;
    ngx_rtmp_netcall_init_t         ci;
    ngx_url_t                      *url;

    if (s->auto_pushed || s->relay) {
        goto next;
    }

    nscf = ngx_rtmp_get_module_srv_conf(s, ngx_rtmp_notify_module);

    url = nscf->url[NGX_RTMP_NOTIFY_DISCONNECT];
    if (url == NULL) {
        goto next;
    }

    ngx_log_error(NGX_LOG_INFO, s->connection->log, 0,
                  "notify: disconnect '%V'", &url->url);

    ngx_memzero(&ci, sizeof(ci));

    ci.url = url;
    ci.create = ngx_rtmp_notify_disconnect_create;

    ngx_rtmp_netcall_create(s, &ci);

next:
    return next_disconnect(s);
}