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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int NGX_ERROR ; 
 int /*<<< orphan*/ * ngx_snprintf (int /*<<< orphan*/ *,size_t,char*) ; 

int
ngx_http_lua_ffi_errlog_set_filter_level(int level, u_char *err, size_t *errlen)
{
#ifdef HAVE_INTERCEPT_ERROR_LOG_PATCH
    ngx_http_lua_log_ringbuf_t     *ringbuf;

    ringbuf = ngx_cycle->intercept_error_log_data;

    if (ringbuf == NULL) {
        *errlen = ngx_snprintf(err, *errlen,
                               "directive \"lua_capture_error_log\" is not set")
                  - err;
        return NGX_ERROR;
    }

    if (level > NGX_LOG_DEBUG || level < NGX_LOG_STDERR) {
        *errlen = ngx_snprintf(err, *errlen, "bad log level: %d", level)
                  - err;
        return NGX_ERROR;
    }

    ringbuf->filter_level = level;
    return NGX_OK;
#else
    *errlen = ngx_snprintf(err, *errlen,
                           "missing the capture error log patch for nginx")
              - err;
    return NGX_ERROR;
#endif
}