#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
struct TYPE_3__ {int /*<<< orphan*/  log; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ ngx_ssl_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_SSL_BUFSIZE ; 
 int /*<<< orphan*/  SSL_CTX_set_early_data_enabled (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_max_early_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

ngx_int_t
ngx_ssl_early_data(ngx_conf_t *cf, ngx_ssl_t *ssl, ngx_uint_t enable)
{
    if (!enable) {
        return NGX_OK;
    }

#ifdef SSL_ERROR_EARLY_DATA_REJECTED

    /* BoringSSL */

    SSL_CTX_set_early_data_enabled(ssl->ctx, 1);

#elif defined SSL_READ_EARLY_DATA_SUCCESS

    /* OpenSSL */

    SSL_CTX_set_max_early_data(ssl->ctx, NGX_SSL_BUFSIZE);

#else
    ngx_log_error(NGX_LOG_WARN, ssl->log, 0,
                  "\"ssl_early_data\" is not supported on this platform, "
                  "ignored");
#endif

    return NGX_OK;
}