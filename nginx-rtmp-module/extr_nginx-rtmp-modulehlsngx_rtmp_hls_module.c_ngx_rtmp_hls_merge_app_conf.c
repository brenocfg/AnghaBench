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
typedef  TYPE_4__ ngx_rtmp_hls_cleanup_t ;
struct TYPE_17__ {int fraglen; int max_fraglen; int muxdelay; int sync; int playlen; scalar_t__ naming; scalar_t__ slicing; scalar_t__ type; int max_audio_delay; scalar_t__ frags_per_key; int winfrags; TYPE_8__ path; TYPE_8__ key_path; TYPE_11__* slot; scalar_t__ cleanup; scalar_t__ keys; scalar_t__ hls; TYPE_8__ key_url; scalar_t__ granularity; TYPE_8__ base_url; int /*<<< orphan*/  audio_buffer_size; scalar_t__ nested; scalar_t__ continuous; } ;
typedef  TYPE_5__ ngx_rtmp_hls_app_conf_t ;
struct TYPE_18__ {TYPE_2__* conf_file; int /*<<< orphan*/  pool; } ;
typedef  TYPE_6__ ngx_conf_t ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
struct TYPE_15__ {TYPE_1__ name; } ;
struct TYPE_14__ {int /*<<< orphan*/  line; TYPE_3__ file; } ;
struct TYPE_12__ {int /*<<< orphan*/  line; int /*<<< orphan*/  conf_file; TYPE_4__* data; TYPE_8__ name; void* manager; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_RTMP_HLS_BUFSIZE ; 
 int /*<<< orphan*/  NGX_RTMP_HLS_NAMING_SEQUENTIAL ; 
 int /*<<< orphan*/  NGX_RTMP_HLS_SLICING_PLAIN ; 
 scalar_t__ NGX_RTMP_HLS_TYPE_EVENT ; 
 int /*<<< orphan*/  NGX_RTMP_HLS_TYPE_LIVE ; 
 scalar_t__ ngx_add_path (TYPE_6__*,TYPE_11__**) ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int,int,int) ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (TYPE_8__,TYPE_8__,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (scalar_t__,scalar_t__,int) ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 void* ngx_rtmp_hls_cleanup ; 
 scalar_t__ ngx_strcmp (char*,char*) ; 

__attribute__((used)) static char *
ngx_rtmp_hls_merge_app_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_rtmp_hls_app_conf_t    *prev = parent;
    ngx_rtmp_hls_app_conf_t    *conf = child;
    ngx_rtmp_hls_cleanup_t     *cleanup;

    ngx_conf_merge_value(conf->hls, prev->hls, 0);
    ngx_conf_merge_msec_value(conf->fraglen, prev->fraglen, 5000);
    ngx_conf_merge_msec_value(conf->max_fraglen, prev->max_fraglen,
                              conf->fraglen * 10);
    ngx_conf_merge_msec_value(conf->muxdelay, prev->muxdelay, 700);
    ngx_conf_merge_msec_value(conf->sync, prev->sync, 2);
    ngx_conf_merge_msec_value(conf->playlen, prev->playlen, 30000);
    ngx_conf_merge_value(conf->continuous, prev->continuous, 1);
    ngx_conf_merge_value(conf->nested, prev->nested, 0);
    ngx_conf_merge_uint_value(conf->naming, prev->naming,
                              NGX_RTMP_HLS_NAMING_SEQUENTIAL);
    ngx_conf_merge_uint_value(conf->slicing, prev->slicing,
                              NGX_RTMP_HLS_SLICING_PLAIN);
    ngx_conf_merge_uint_value(conf->type, prev->type,
                              NGX_RTMP_HLS_TYPE_LIVE);
    ngx_conf_merge_msec_value(conf->max_audio_delay, prev->max_audio_delay,
                              300);
    ngx_conf_merge_size_value(conf->audio_buffer_size, prev->audio_buffer_size,
                              NGX_RTMP_HLS_BUFSIZE);
    ngx_conf_merge_value(conf->cleanup, prev->cleanup, 1);
    ngx_conf_merge_str_value(conf->base_url, prev->base_url, "");
    ngx_conf_merge_value(conf->granularity, prev->granularity, 0);
    ngx_conf_merge_value(conf->keys, prev->keys, 0);
    ngx_conf_merge_str_value(conf->key_path, prev->key_path, "");
    ngx_conf_merge_str_value(conf->key_url, prev->key_url, "");
    ngx_conf_merge_uint_value(conf->frags_per_key, prev->frags_per_key, 0);

    if (conf->fraglen) {
        conf->winfrags = conf->playlen / conf->fraglen;
    }

    /* schedule cleanup */

    if (conf->hls && conf->path.len && conf->cleanup &&
        conf->type != NGX_RTMP_HLS_TYPE_EVENT)
    {
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

        conf->slot->manager = ngx_rtmp_hls_cleanup;
        conf->slot->name = conf->path;
        conf->slot->data = cleanup;
        conf->slot->conf_file = cf->conf_file->file.name.data;
        conf->slot->line = cf->conf_file->line;

        if (ngx_add_path(cf, &conf->slot) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

    ngx_conf_merge_str_value(conf->path, prev->path, "");

    if (conf->keys && conf->cleanup && conf->key_path.len &&
        ngx_strcmp(conf->key_path.data, conf->path.data) != 0 &&
        conf->type != NGX_RTMP_HLS_TYPE_EVENT)
    {
        if (conf->key_path.data[conf->key_path.len - 1] == '/') {
            conf->key_path.len--;
        }

        cleanup = ngx_pcalloc(cf->pool, sizeof(*cleanup));
        if (cleanup == NULL) {
            return NGX_CONF_ERROR;
        }

        cleanup->path = conf->key_path;
        cleanup->playlen = conf->playlen;

        conf->slot = ngx_pcalloc(cf->pool, sizeof(*conf->slot));
        if (conf->slot == NULL) {
            return NGX_CONF_ERROR;
        }

        conf->slot->manager = ngx_rtmp_hls_cleanup;
        conf->slot->name = conf->key_path;
        conf->slot->data = cleanup;
        conf->slot->conf_file = cf->conf_file->file.name.data;
        conf->slot->line = cf->conf_file->line;

        if (ngx_add_path(cf, &conf->slot) != NGX_OK) {
            return NGX_CONF_ERROR;
        }
    }

    ngx_conf_merge_str_value(conf->key_path, prev->key_path, "");

    if (conf->key_path.len == 0) {
        conf->key_path = conf->path;
    }

    return NGX_CONF_OK;
}