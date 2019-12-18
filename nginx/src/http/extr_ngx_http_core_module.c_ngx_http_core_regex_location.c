#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
typedef  void* ngx_str_t ;
struct TYPE_7__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {void* options; TYPE_1__ err; void* pattern; } ;
typedef  TYPE_2__ ngx_regex_compile_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_9__ {void* name; int /*<<< orphan*/ * regex; } ;
typedef  TYPE_3__ ngx_http_core_loc_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int NGX_MAX_CONF_ERRSTR ; 
 int /*<<< orphan*/  NGX_OK ; 
 void* NGX_REGEX_CASELESS ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/ * ngx_http_regex_compile (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 

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