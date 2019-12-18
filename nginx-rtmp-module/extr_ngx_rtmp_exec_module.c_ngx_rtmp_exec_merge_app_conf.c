#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_6__ {int nbuckets; int active; int /*<<< orphan*/ * pull; TYPE_3__* conf; int /*<<< orphan*/  respawn; } ;
typedef  TYPE_1__ ngx_rtmp_exec_app_conf_t ;
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ ngx_conf_t ;
struct TYPE_8__ {scalar_t__ nelts; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 size_t NGX_RTMP_EXEC_MAX ; 
 size_t NGX_RTMP_EXEC_PULL ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int,int,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_rtmp_exec_merge_confs (TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static char *
ngx_rtmp_exec_merge_app_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_rtmp_exec_app_conf_t   *prev = parent;
    ngx_rtmp_exec_app_conf_t   *conf = child;

    ngx_uint_t  n;

    ngx_conf_merge_value(conf->respawn, prev->respawn, 1);
    ngx_conf_merge_uint_value(conf->nbuckets, prev->nbuckets, 1024);

    for (n = 0; n < NGX_RTMP_EXEC_MAX; n++) {
        if (ngx_rtmp_exec_merge_confs(&conf->conf[n], &prev->conf[n]) != NGX_OK)
        {
            return NGX_CONF_ERROR;
        }

        if (conf->conf[n].nelts) {
            conf->active = 1;
            prev->active = 1;
        }
    }

    if (conf->conf[NGX_RTMP_EXEC_PULL].nelts > 0) {
        conf->pull = ngx_pcalloc(cf->pool, sizeof(void *) * conf->nbuckets);
        if (conf->pull == NULL) {
            return NGX_CONF_ERROR;
        }
    }

    return NGX_CONF_OK;
}