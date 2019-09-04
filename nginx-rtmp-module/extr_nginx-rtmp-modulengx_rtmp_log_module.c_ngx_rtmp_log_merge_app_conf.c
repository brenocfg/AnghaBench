#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * format; scalar_t__ error_log_time; scalar_t__ disk_full_time; int /*<<< orphan*/ * file; } ;
typedef  TYPE_2__ ngx_rtmp_log_t ;
struct TYPE_10__ {int /*<<< orphan*/ * elts; } ;
struct TYPE_12__ {int combined_used; TYPE_1__ formats; } ;
typedef  TYPE_3__ ngx_rtmp_log_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_log_fmt_t ;
struct TYPE_13__ {int /*<<< orphan*/ * logs; scalar_t__ off; } ;
typedef  TYPE_4__ ngx_rtmp_log_app_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 char* NGX_OK ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_conf_open_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_rtmp_access_log ; 
 TYPE_3__* ngx_rtmp_conf_get_module_main_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_log_module ; 

__attribute__((used)) static char *
ngx_rtmp_log_merge_app_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_rtmp_log_app_conf_t    *prev = parent;
    ngx_rtmp_log_app_conf_t    *conf = child;
    ngx_rtmp_log_main_conf_t   *lmcf;
    ngx_rtmp_log_fmt_t         *fmt;
    ngx_rtmp_log_t             *log;

    if (conf->logs || conf->off) {
        return NGX_OK;
    }

    conf->logs = prev->logs;
    conf->off = prev->off;

    if (conf->logs || conf->off) {
        return NGX_OK;
    }

    conf->logs = ngx_array_create(cf->pool, 2, sizeof(ngx_rtmp_log_t));
    if (conf->logs == NULL) {
        return NGX_CONF_ERROR;
    }

    log = ngx_array_push(conf->logs);
    if (log == NULL) {
        return NGX_CONF_ERROR;
    }

    log->file = ngx_conf_open_file(cf->cycle, &ngx_rtmp_access_log);
    if (log->file == NULL) {
        return NGX_CONF_ERROR;
    }

    log->disk_full_time = 0;
    log->error_log_time = 0;

    lmcf = ngx_rtmp_conf_get_module_main_conf(cf, ngx_rtmp_log_module);
    fmt = lmcf->formats.elts;

    log->format = &fmt[0];
    lmcf->combined_used = 1;

    return NGX_CONF_OK;
}