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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_http_perl_preconfiguration(ngx_conf_t *cf)
{
#if (NGX_HTTP_SSI)
    ngx_int_t                  rc;
    ngx_http_ssi_main_conf_t  *smcf;

    smcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_ssi_filter_module);

    rc = ngx_hash_add_key(&smcf->commands, &ngx_http_perl_ssi_command.name,
                          &ngx_http_perl_ssi_command, NGX_HASH_READONLY_KEY);

    if (rc != NGX_OK) {
        if (rc == NGX_BUSY) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "conflicting SSI command \"%V\"",
                               &ngx_http_perl_ssi_command.name);
        }

        return NGX_ERROR;
    }
#endif

    return NGX_OK;
}