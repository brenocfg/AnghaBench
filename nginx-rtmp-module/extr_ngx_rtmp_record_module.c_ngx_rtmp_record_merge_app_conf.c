#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rec; scalar_t__ flags; int /*<<< orphan*/  url; int /*<<< orphan*/  interval; int /*<<< orphan*/  notify; int /*<<< orphan*/  lock_file; int /*<<< orphan*/  append; int /*<<< orphan*/  unique; int /*<<< orphan*/  max_frames; int /*<<< orphan*/  max_size; int /*<<< orphan*/  suffix; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ ngx_rtmp_record_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_CONF_UNSET ; 
 TYPE_1__** ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_bitmask_value (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_msec_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_size_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_conf_merge_str_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_conf_merge_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_rtmp_record_merge_app_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_rtmp_record_app_conf_t     *prev = parent;
    ngx_rtmp_record_app_conf_t     *conf = child;
    ngx_rtmp_record_app_conf_t    **rracf;

    ngx_conf_merge_str_value(conf->path, prev->path, "");
    ngx_conf_merge_str_value(conf->suffix, prev->suffix, ".flv");
    ngx_conf_merge_size_value(conf->max_size, prev->max_size, 0);
    ngx_conf_merge_size_value(conf->max_frames, prev->max_frames, 0);
    ngx_conf_merge_value(conf->unique, prev->unique, 0);
    ngx_conf_merge_value(conf->append, prev->append, 0);
    ngx_conf_merge_value(conf->lock_file, prev->lock_file, 0);
    ngx_conf_merge_value(conf->notify, prev->notify, 0);
    ngx_conf_merge_msec_value(conf->interval, prev->interval,
                              (ngx_msec_t) NGX_CONF_UNSET);
    ngx_conf_merge_bitmask_value(conf->flags, prev->flags, 0);
    ngx_conf_merge_ptr_value(conf->url, prev->url, NULL);

    if (conf->flags) {
        rracf = ngx_array_push(&conf->rec);
        if (rracf == NULL) {
            return NGX_CONF_ERROR;
        }

        *rracf = conf;
    }

    return NGX_CONF_OK;
}