#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* handler_conf; int /*<<< orphan*/  handler; } ;
typedef  TYPE_1__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;

/* Variables and functions */
 char* ngx_http_lua_conf_lua_block_parse (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_init_worker_by_lua ; 

char *
ngx_http_lua_init_worker_by_lua_block(ngx_conf_t *cf, ngx_command_t *cmd,
    void *conf)
{
    char        *rv;
    ngx_conf_t   save;

    save = *cf;
    cf->handler = ngx_http_lua_init_worker_by_lua;
    cf->handler_conf = conf;

    rv = ngx_http_lua_conf_lua_block_parse(cf, cmd);

    *cf = save;

    return rv;
}