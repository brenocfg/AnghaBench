#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_9__ {int /*<<< orphan*/ * mirror; } ;
typedef  TYPE_3__ ngx_http_mirror_loc_conf_t ;
struct TYPE_10__ {int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_4__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_7__ {TYPE_2__* elts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * NGX_CONF_UNSET_PTR ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_2__* ngx_array_push (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
ngx_http_mirror(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_mirror_loc_conf_t *mlcf = conf;

    ngx_str_t  *value, *s;

    value = cf->args->elts;

    if (ngx_strcmp(value[1].data, "off") == 0) {
        if (mlcf->mirror != NGX_CONF_UNSET_PTR) {
            return "is duplicate";
        }

        mlcf->mirror = NULL;
        return NGX_CONF_OK;
    }

    if (mlcf->mirror == NULL) {
        return "is duplicate";
    }

    if (mlcf->mirror == NGX_CONF_UNSET_PTR) {
        mlcf->mirror = ngx_array_create(cf->pool, 4, sizeof(ngx_str_t));
        if (mlcf->mirror == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    s = ngx_array_push(mlcf->mirror);
    if (s == NULL) {
        return NGX_CONF_ERROR;
    }

    *s = value[1];

    return NGX_CONF_OK;
}