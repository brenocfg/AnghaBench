#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_2__ ngx_url_t ;
struct TYPE_17__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_18__ {TYPE_2__** url; } ;
typedef  TYPE_4__ ngx_rtmp_notify_app_conf_t ;
struct TYPE_19__ {int /*<<< orphan*/  (* handle ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  create; TYPE_2__* url; } ;
typedef  TYPE_5__ ngx_rtmp_netcall_init_t ;
struct TYPE_20__ {TYPE_7__* data; } ;
typedef  TYPE_6__ ngx_event_t ;
struct TYPE_21__ {TYPE_3__* data; } ;
typedef  TYPE_7__ ngx_connection_t ;
typedef  int /*<<< orphan*/  ci ;
struct TYPE_15__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 size_t NGX_RTMP_NOTIFY_UPDATE ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 TYPE_4__* ngx_rtmp_get_module_app_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_rtmp_netcall_create (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_rtmp_notify_module ; 
 int /*<<< orphan*/  ngx_rtmp_notify_update_create ; 
 int /*<<< orphan*/  ngx_rtmp_notify_update_handle (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_rtmp_notify_update(ngx_event_t *e)
{
    ngx_connection_t           *c;
    ngx_rtmp_session_t         *s;
    ngx_rtmp_notify_app_conf_t *nacf;
    ngx_rtmp_netcall_init_t     ci;
    ngx_url_t                  *url;

    c = e->data;
    s = c->data;

    nacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_notify_module);

    url = nacf->url[NGX_RTMP_NOTIFY_UPDATE];

    ngx_log_error(NGX_LOG_INFO, s->connection->log, 0,
                  "notify: update '%V'", &url->url);

    ngx_memzero(&ci, sizeof(ci));

    ci.url = url;
    ci.create = ngx_rtmp_notify_update_create;
    ci.handle = ngx_rtmp_notify_update_handle;

    if (ngx_rtmp_netcall_create(s, &ci) == NGX_OK) {
        return;
    }

    /* schedule next update on connection error */

    ngx_rtmp_notify_update_handle(s, NULL, NULL);
}