#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_26__ {TYPE_3__* connection; scalar_t__ relay; } ;
typedef  TYPE_6__ ngx_rtmp_session_t ;
struct TYPE_24__ {int /*<<< orphan*/  url; } ;
struct TYPE_22__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_27__ {TYPE_4__ url; int /*<<< orphan*/  play_path; int /*<<< orphan*/  app; TYPE_2__ name; } ;
typedef  TYPE_7__ ngx_rtmp_relay_target_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_relay_ctx_t ;
struct TYPE_21__ {size_t nelts; TYPE_7__** elts; } ;
struct TYPE_28__ {TYPE_1__ pulls; } ;
typedef  TYPE_8__ ngx_rtmp_relay_app_conf_t ;
struct TYPE_29__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_9__ ngx_rtmp_play_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  next_play (TYPE_6__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_8__* ngx_rtmp_get_module_app_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_rtmp_get_module_ctx (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_relay_module ; 
 scalar_t__ ngx_rtmp_relay_pull (TYPE_6__*,TYPE_5__*,TYPE_7__*) ; 
 scalar_t__ ngx_strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_relay_play(ngx_rtmp_session_t *s, ngx_rtmp_play_t *v)
{
    ngx_rtmp_relay_app_conf_t      *racf;
    ngx_rtmp_relay_target_t        *target, **t;
    ngx_str_t                       name;
    size_t                          n;
    ngx_rtmp_relay_ctx_t           *ctx;

    ctx = ngx_rtmp_get_module_ctx(s, ngx_rtmp_relay_module);
    if (ctx && s->relay) {
        goto next;
    }

    racf = ngx_rtmp_get_module_app_conf(s, ngx_rtmp_relay_module);
    if (racf == NULL || racf->pulls.nelts == 0) {
        goto next;
    }

    name.len = ngx_strlen(v->name);
    name.data = v->name;

    t = racf->pulls.elts;
    for (n = 0; n < racf->pulls.nelts; ++n, ++t) {
        target = *t;

        if (target->name.len && (name.len != target->name.len ||
            ngx_memcmp(name.data, target->name.data, name.len)))
        {
            continue;
        }

        if (ngx_rtmp_relay_pull(s, &name, target) == NGX_OK) {
            continue;
        }

        ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                "relay: pull failed name='%V' app='%V' "
                "playpath='%V' url='%V'",
                &name, &target->app, &target->play_path,
                &target->url.url);
    }

next:
    return next_play(s, v);
}