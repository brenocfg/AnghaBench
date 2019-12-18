#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_22__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_23__ {TYPE_7__* format; int /*<<< orphan*/ * file; } ;
typedef  TYPE_5__ ngx_rtmp_log_t ;
struct TYPE_20__ {scalar_t__ nelts; TYPE_7__* elts; } ;
struct TYPE_24__ {int combined_used; TYPE_2__ formats; } ;
typedef  TYPE_6__ ngx_rtmp_log_main_conf_t ;
struct TYPE_21__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_25__ {TYPE_3__ name; } ;
typedef  TYPE_7__ ngx_rtmp_log_fmt_t ;
struct TYPE_26__ {int off; int /*<<< orphan*/ * logs; } ;
typedef  TYPE_8__ ngx_rtmp_log_app_conf_t ;
struct TYPE_27__ {TYPE_1__* args; int /*<<< orphan*/  cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_9__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_19__ {int nelts; TYPE_4__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_5__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/ * ngx_conf_open_file (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 TYPE_6__* ngx_rtmp_conf_get_module_main_conf (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_log_module ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_4__*,char*) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static char *
ngx_rtmp_log_set_log(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_rtmp_log_app_conf_t    *lacf = conf;

    ngx_rtmp_log_main_conf_t   *lmcf;
    ngx_rtmp_log_fmt_t         *fmt;
    ngx_rtmp_log_t             *log;
    ngx_str_t                  *value, name;
    ngx_uint_t                  n;

    value = cf->args->elts;

    if (ngx_strcmp(value[1].data, "off") == 0) {
        lacf->off = 1;
        return NGX_CONF_OK;
    }

    if (lacf->logs == NULL) {
        lacf->logs = ngx_array_create(cf->pool, 2, sizeof(ngx_rtmp_log_t));
        if (lacf->logs == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    log = ngx_array_push(lacf->logs);
    if (log == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(log, sizeof(*log));

    lmcf = ngx_rtmp_conf_get_module_main_conf(cf, ngx_rtmp_log_module);

    log->file = ngx_conf_open_file(cf->cycle, &value[1]);
    if (log->file == NULL) {
        return NGX_CONF_ERROR;
    }

    if (cf->args->nelts == 2) {
        ngx_str_set(&name, "combined");
        lmcf->combined_used = 1;

    } else {
        name = value[2];
        if (ngx_strcmp(name.data, "combined") == 0) {
            lmcf->combined_used = 1;
        }
    }

    fmt = lmcf->formats.elts;
    for (n = 0; n < lmcf->formats.nelts; ++n, ++fmt) {
        if (fmt->name.len == name.len &&
            ngx_strncasecmp(fmt->name.data, name.data, name.len) == 0)
        {
            log->format = fmt;
            break;
        }
    }

    if (log->format == NULL) {
        ngx_conf_log_error(NGX_LOG_WARN, cf, 0, "unknown log format \"%V\"",
                           &name);
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}