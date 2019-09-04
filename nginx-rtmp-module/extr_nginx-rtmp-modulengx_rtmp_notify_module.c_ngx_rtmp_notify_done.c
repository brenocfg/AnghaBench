#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_14__ {int /*<<< orphan*/  url; } ;
typedef  TYPE_2__ ngx_url_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {TYPE_1__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_16__ {size_t url_idx; int /*<<< orphan*/ * cbname; } ;
typedef  TYPE_4__ ngx_rtmp_notify_done_t ;
struct TYPE_17__ {TYPE_2__** url; } ;
typedef  TYPE_5__ ngx_rtmp_notify_app_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  create; TYPE_4__* arg; TYPE_2__* url; } ;
typedef  TYPE_6__ ngx_rtmp_netcall_init_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ci ;
struct TYPE_13__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_6__*,int) ; 
 TYPE_5__* ngx_rtmp_get_module_app_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_netcall_create (TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_rtmp_notify_done_create ; 
 int /*<<< orphan*/  ngx_rtmp_notify_module ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_notify_done(ngx_rtmp_session_t *s, char *cbname, ngx_uint_t url_idx)
{
    ngx_rtmp_netcall_init_t         ci;
    ngx_rtmp_notify_done_t          ds;
    ngx_rtmp_notify_app_conf_t     *nacf;
    ngx_url_t                      *url;

    nacf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_notify_module);

    url = nacf->url[url_idx];
    if (url == NULL) {
        return NGX_OK;
    }

    ngx_log_error(NGX_LOG_INFO, s->connection->log, 0,
                  "notify: %s '%V'", cbname, &url->url);

    ds.cbname = (u_char *) cbname;
    ds.url_idx = url_idx;

    ngx_memzero(&ci, sizeof(ci));

    ci.url = url;
    ci.arg = &ds;
    ci.create = ngx_rtmp_notify_done_create;

    return ngx_rtmp_netcall_create(s, &ci);
}