#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; scalar_t__* level; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ngx_path_t ;
struct TYPE_12__ {scalar_t__* level; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ngx_path_init_t ;
struct TYPE_13__ {int /*<<< orphan*/  cycle; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 size_t NGX_MAX_PATH_LEVEL ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_add_path (TYPE_3__*,TYPE_1__**) ; 
 scalar_t__ ngx_conf_full_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

char *
ngx_conf_merge_path_value(ngx_conf_t *cf, ngx_path_t **path, ngx_path_t *prev,
    ngx_path_init_t *init)
{
    ngx_uint_t  i;

    if (*path) {
        return NGX_CONF_OK;
    }

    if (prev) {
        *path = prev;
        return NGX_CONF_OK;
    }

    *path = ngx_pcalloc(cf->pool, sizeof(ngx_path_t));
    if (*path == NULL) {
        return NGX_CONF_ERROR;
    }

    (*path)->name = init->name;

    if (ngx_conf_full_name(cf->cycle, &(*path)->name, 0) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    for (i = 0; i < NGX_MAX_PATH_LEVEL; i++) {
        (*path)->level[i] = init->level[i];
        (*path)->len += init->level[i] + (init->level[i] ? 1 : 0);
    }

    if (ngx_add_path(cf, path) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}