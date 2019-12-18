#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {int len; char* data; } ;
struct TYPE_16__ {int playlen; TYPE_8__ path; } ;
typedef  TYPE_4__ ngx_rtmp_dash_cleanup_t ;
struct TYPE_17__ {int fraglen; int playlen; int winfrags; TYPE_8__ path; TYPE_11__* slot; scalar_t__ cleanup; scalar_t__ dash; scalar_t__ nested; } ;
typedef  TYPE_5__ ngx_rtmp_dash_app_conf_t ;
struct TYPE_18__ {TYPE_3__* conf_file; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
struct TYPE_14__ {TYPE_1__ name; } ;
struct TYPE_15__ {int /*<<< orphan*/  line; TYPE_2__ file; } ;
struct TYPE_12__ {int /*<<< orphan*/  line; int /*<<< orphan*/  conf_file; TYPE_4__* data; TYPE_8__ name; int /*<<< orphan*/  manager; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_add_path (TYPE_6__*,TYPE_11__**) ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int,int,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (TYPE_8__,TYPE_8__,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (scalar_t__,scalar_t__,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_rtmp_dash_cleanup ; 

__attribute__((used)) static char *
ngx_rtmp_dash_merge_app_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_rtmp_dash_app_conf_t    *prev = parent;
    ngx_rtmp_dash_app_conf_t    *conf = child;
    ngx_rtmp_dash_cleanup_t     *cleanup;

    ngx_conf_merge_value(conf->dash, prev->dash, 0);
    ngx_conf_merge_msec_value(conf->fraglen, prev->fraglen, 5000);
    ngx_conf_merge_msec_value(conf->playlen, prev->playlen, 30000);
    ngx_conf_merge_value(conf->cleanup, prev->cleanup, 1);
    ngx_conf_merge_value(conf->nested, prev->nested, 0);

    if (conf->fraglen) {
        conf->winfrags = conf->playlen / conf->fraglen;
    }

    /* schedule cleanup */

    if (conf->dash && conf->path.len && conf->cleanup) {
        if (conf->path.data[conf->path.len - 1] == '/') {
            conf->path.len--;
        }

        cleanup = ngx_pcalloc(cf->pool, sizeof(*cleanup));
        if (cleanup == NULL) {
            return NGX_CONF_ERROR;
        }

        cleanup->path = conf->path;
        cleanup->playlen = conf->playlen;

        conf->slot = ngx_pcalloc(cf->pool, sizeof(*conf->slot));
        if (conf->slot == NULL) {
            return NGX_CONF_ERROR;
        }

        conf->slot->manager = ngx_rtmp_dash_cleanup;
        conf->slot->name = conf->path;
        conf->slot->data = cleanup;
        conf->slot->conf_file = cf->conf_file->file.name.data;
        conf->slot->line = cf->conf_file->line;

        if (ngx_add_path(cf, &conf->slot) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

    ngx_conf_merge_str_value(conf->path, prev->path, "");

    return NGX_CONF_OK;
}