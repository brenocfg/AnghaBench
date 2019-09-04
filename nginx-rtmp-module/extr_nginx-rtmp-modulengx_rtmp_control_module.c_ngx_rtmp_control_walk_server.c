#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_11__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_9__ {scalar_t__ nelts; TYPE_5__** elts; } ;
struct TYPE_12__ {TYPE_1__ applications; } ;
typedef  TYPE_4__ ngx_rtmp_core_srv_conf_t ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_2__ name; } ;
typedef  TYPE_5__ ngx_rtmp_core_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;

/* Variables and functions */
 char const* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_3__*) ; 
 char* ngx_rtmp_control_walk_app (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static const char *
ngx_rtmp_control_walk_server(ngx_http_request_t *r,
    ngx_rtmp_core_srv_conf_t *cscf)
{
    ngx_str_t                   app;
    ngx_uint_t                  n;
    const char                 *s;
    ngx_rtmp_core_app_conf_t  **pcacf;

    if (ngx_http_arg(r, (u_char *) "app", sizeof("app") - 1, &app) != NGX_OK) {
        app.len = 0;
    }

    pcacf = cscf->applications.elts;

    for (n = 0; n < cscf->applications.nelts; ++n, ++pcacf) {
        if (app.len && ((*pcacf)->name.len != app.len ||
                        ngx_strncmp((*pcacf)->name.data, app.data, app.len)))
        {
            continue;
        }

        s = ngx_rtmp_control_walk_app(r, *pcacf);
        if (s != NGX_CONF_OK) {
            return s;
        }
    }

    return NGX_CONF_OK;
}