#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  void* ngx_str_t ;
struct TYPE_12__ {void* err; int captures; int /*<<< orphan*/  regex; int /*<<< orphan*/  pool; void* pattern; } ;
typedef  TYPE_2__ ngx_regex_compile_t ;
struct TYPE_13__ {int /*<<< orphan*/  split_regex; void* split_name; } ;
typedef  TYPE_3__ ngx_http_fastcgi_loc_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
struct TYPE_15__ {void* name; } ;
typedef  TYPE_5__ ngx_command_t ;
struct TYPE_11__ {void** elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int NGX_MAX_CONF_ERRSTR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_2__*,int) ; 
 scalar_t__ ngx_regex_compile (TYPE_2__*) ; 

__attribute__((used)) static char *
ngx_http_fastcgi_split_path_info(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
#if (NGX_PCRE)
    ngx_http_fastcgi_loc_conf_t *flcf = conf;

    ngx_str_t            *value;
    ngx_regex_compile_t   rc;
    u_char                errstr[NGX_MAX_CONF_ERRSTR];

    value = cf->args->elts;

    flcf->split_name = value[1];

    ngx_memzero(&rc, sizeof(ngx_regex_compile_t));

    rc.pattern = value[1];
    rc.pool = cf->pool;
    rc.err.len = NGX_MAX_CONF_ERRSTR;
    rc.err.data = errstr;

    if (ngx_regex_compile(&rc) != NGX_OK) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "%V", &rc.err);
        return NGX_CONF_ERROR;
    }

    if (rc.captures != 2) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "pattern \"%V\" must have 2 captures", &value[1]);
        return NGX_CONF_ERROR;
    }

    flcf->split_regex = rc.regex;

    return NGX_CONF_OK;

#else

    ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                       "\"%V\" requires PCRE library", &cmd->name);
    return NGX_CONF_ERROR;

#endif
}