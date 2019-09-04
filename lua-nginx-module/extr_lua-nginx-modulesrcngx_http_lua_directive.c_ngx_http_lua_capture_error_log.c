#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;

/* Variables and functions */

char *
ngx_http_lua_capture_error_log(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
#ifndef HAVE_INTERCEPT_ERROR_LOG_PATCH
    return "not found: missing the capture error log patch for nginx";
#else
    ngx_str_t                     *value;
    ssize_t                        size;
    u_char                        *data;
    ngx_cycle_t                   *cycle;
    ngx_http_lua_main_conf_t      *lmcf = conf;
    ngx_http_lua_log_ringbuf_t    *ringbuf;

    value = cf->args->elts;
    cycle = cf->cycle;

    if (lmcf->requires_capture_log) {
        return "is duplicate";
    }

    if (value[1].len == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid capture error log size \"%V\"",
                           &value[1]);
        return NGX_CONF_ERROR;
    }

    size = ngx_parse_size(&value[1]);

    if (size < NGX_MAX_ERROR_STR) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "invalid capture error log size \"%V\", "
                           "minimum size is %d", &value[1],
                           NGX_MAX_ERROR_STR);
        return NGX_CONF_ERROR;
    }

    if (cycle->intercept_error_log_handler) {
        return "capture error log handler has been hooked";
    }

    ringbuf = (ngx_http_lua_log_ringbuf_t *)
              ngx_palloc(cf->pool, sizeof(ngx_http_lua_log_ringbuf_t));
    if (ringbuf == NULL) {
        return NGX_CONF_ERROR;
    }

    data = ngx_palloc(cf->pool, size);
    if (data == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_http_lua_log_ringbuf_init(ringbuf, data, size);

    lmcf->requires_capture_log = 1;
    cycle->intercept_error_log_handler = (ngx_log_intercept_pt)
                                         ngx_http_lua_capture_log_handler;
    cycle->intercept_error_log_data = ringbuf;

    return NGX_CONF_OK;
#endif
}