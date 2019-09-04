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
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_core_regex_location(ngx_conf_t *cf, ngx_http_core_loc_conf_t *clcf,
    ngx_str_t *regex, ngx_uint_t caseless)
{
#if (NGX_PCRE)
    ngx_regex_compile_t  rc;
    u_char               errstr[NGX_MAX_CONF_ERRSTR];

    ngx_memzero(&rc, sizeof(ngx_regex_compile_t));

    rc.pattern = *regex;
    rc.err.len = NGX_MAX_CONF_ERRSTR;
    rc.err.data = errstr;

#if (NGX_HAVE_CASELESS_FILESYSTEM)
    rc.options = NGX_REGEX_CASELESS;
#else
    rc.options = caseless ? NGX_REGEX_CASELESS : 0;
#endif

    clcf->regex = ngx_http_regex_compile(cf, &rc);
    if (clcf->regex == NULL) {
        return NGX_ERROR;
    }

    clcf->name = *regex;

    return NGX_OK;

#else

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "using regex \"%V\" requires PCRE library",
                       regex);
    return NGX_ERROR;

#endif
}