#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_12__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_log_op_t ;
struct TYPE_11__ {size_t nelts; TYPE_3__* elts; } ;
struct TYPE_13__ {TYPE_10__ formats; } ;
typedef  TYPE_2__ ngx_rtmp_log_main_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/ * ops; TYPE_1__ name; } ;
typedef  TYPE_3__ ngx_rtmp_log_fmt_t ;
struct TYPE_15__ {scalar_t__ cmd_type; TYPE_7__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_16__ {TYPE_1__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_RTMP_MAIN_CONF ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* ngx_array_push (TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 char* ngx_rtmp_log_compile_format (TYPE_4__*,int /*<<< orphan*/ *,TYPE_7__*,int) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_rtmp_log_set_format(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_rtmp_log_main_conf_t   *lmcf = conf;
    ngx_rtmp_log_fmt_t         *fmt;
    ngx_str_t                  *value;
    ngx_uint_t                  i;

    value = cf->args->elts;

    if (cf->cmd_type != NGX_RTMP_MAIN_CONF) {
        ngx_conf_log_error(NGX_LOG_WARN, cf, 0,
                           "\"log_format\" directive can only be used on "
                           "\"rtmp\" level");
    }

    fmt = lmcf->formats.elts;
    for (i = 0; i < lmcf->formats.nelts; i++) {
        if (fmt[i].name.len == value[1].len &&
            ngx_strcmp(fmt[i].name.data, value[1].data) == 0)
        {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "duplicate \"log_format\" name \"%V\"",
                               &value[1]);
            return NGX_CONF_ERROR;
        }
    }

    fmt = ngx_array_push(&lmcf->formats);
    if (fmt == NULL) {
        return NGX_CONF_ERROR;
    }

    fmt->name = value[1];

    fmt->ops = ngx_array_create(cf->pool, 16, sizeof(ngx_rtmp_log_op_t));
    if (fmt->ops == NULL) {
        return NGX_CONF_ERROR;
    }

    return ngx_rtmp_log_compile_format(cf, fmt->ops, cf->args, 2);
}