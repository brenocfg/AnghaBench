#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int len; int data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_21__ {scalar_t__ nalloc; } ;
struct TYPE_17__ {TYPE_7__ args; TYPE_7__ names; TYPE_2__ cmd; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ ngx_rtmp_exec_conf_t ;
struct TYPE_18__ {int options; } ;
typedef  TYPE_4__ ngx_rtmp_exec_app_conf_t ;
struct TYPE_19__ {TYPE_1__* args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_conf_t ;
struct TYPE_20__ {int offset; } ;
typedef  TYPE_6__ ngx_command_t ;
typedef  TYPE_7__ ngx_array_t ;
struct TYPE_15__ {int nelts; TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_CONF_UNSET_UINT ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_array_init (TYPE_7__*,int /*<<< orphan*/ ,size_t,int) ; 
 void* ngx_array_push (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 TYPE_4__* ngx_rtmp_conf_get_module_app_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_rtmp_exec_module ; 
 scalar_t__ ngx_strncmp (int,char*,int) ; 

__attribute__((used)) static char *
ngx_rtmp_exec_conf(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char  *p = conf;

    size_t                     n, nargs;
    ngx_str_t                 *s, *value, v;
    ngx_array_t               *confs;
    ngx_rtmp_exec_conf_t      *ec;
    ngx_rtmp_exec_app_conf_t  *eacf;

    confs = (ngx_array_t *) (p + cmd->offset);

    eacf = ngx_rtmp_conf_get_module_app_conf(cf, ngx_rtmp_exec_module);

    if (confs->nalloc == 0 && ngx_array_init(confs, cf->pool, 1,
                                             sizeof(ngx_rtmp_exec_conf_t))
                              != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    value = cf->args->elts;

    ec = ngx_array_push(confs);
    if (ec == NULL) {
        return NGX_CONF_ERROR;
    }

    ngx_memzero(ec, sizeof(ngx_rtmp_exec_conf_t));

    /* type is undefined for explicit execs */

    ec->type = NGX_CONF_UNSET_UINT;
    ec->cmd = value[1];

    if (ngx_array_init(&ec->names, cf->pool, 1, sizeof(ngx_str_t)) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    if (cf->args->nelts == 2) {
        return NGX_CONF_OK;
    }

    nargs = cf->args->nelts - 2;
    if (ngx_array_init(&ec->args, cf->pool, nargs, sizeof(ngx_str_t)) != NGX_OK)
    {
        return NGX_CONF_ERROR;
    }

    for (n = 2; n < cf->args->nelts; n++) {

        v = value[n];

        if (eacf->options == 1) {

            if (v.len >= 5 && ngx_strncmp(v.data, "name=", 5) == 0) {

                s = ngx_array_push(&ec->names);
                if (s == NULL) {
                    return NGX_CONF_ERROR;
                }

                v.data += 5;
                v.len -= 5;

                *s = v;

                continue;
            }
        }

        s = ngx_array_push(&ec->args);
        if (s == NULL) {
            return NGX_CONF_ERROR;
        }

        *s = v;
    }

    return NGX_CONF_OK;
}