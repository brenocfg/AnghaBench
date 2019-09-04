#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_1__ ngx_str_t ;
struct TYPE_9__ {int /*<<< orphan*/  log; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ ngx_ssl_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  cycle; } ;
typedef  TYPE_3__ ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ SSL_CTX_load_verify_locations (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify_depth (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ngx_conf_full_name (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ngx_ssl_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 

ngx_int_t
ngx_ssl_trusted_certificate(ngx_conf_t *cf, ngx_ssl_t *ssl, ngx_str_t *cert,
    ngx_int_t depth)
{
    SSL_CTX_set_verify_depth(ssl->ctx, depth);

    if (cert->len == 0) {
        return NGX_OK;
    }

    if (ngx_conf_full_name(cf->cycle, cert, 1) != NGX_OK) {
        return NGX_ERROR;
    }

    if (SSL_CTX_load_verify_locations(ssl->ctx, (char *) cert->data, NULL)
        == 0)
    {
        ngx_ssl_error(NGX_LOG_EMERG, ssl->log, 0,
                      "SSL_CTX_load_verify_locations(\"%s\") failed",
                      cert->data);
        return NGX_ERROR;
    }

    /*
     * SSL_CTX_load_verify_locations() may leave errors in the error queue
     * while returning success
     */

    ERR_clear_error();

    return NGX_OK;
}