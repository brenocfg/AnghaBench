#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ off; scalar_t__ logs; int /*<<< orphan*/ * open_file_cache; int /*<<< orphan*/  open_file_cache_min_uses; int /*<<< orphan*/  open_file_cache_valid; } ;
typedef  TYPE_1__ ngx_stream_log_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/ * NGX_CONF_UNSET_PTR ; 

__attribute__((used)) static char *
ngx_stream_log_merge_srv_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_stream_log_srv_conf_t *prev = parent;
    ngx_stream_log_srv_conf_t *conf = child;

    if (conf->open_file_cache == NGX_CONF_UNSET_PTR) {

        conf->open_file_cache = prev->open_file_cache;
        conf->open_file_cache_valid = prev->open_file_cache_valid;
        conf->open_file_cache_min_uses = prev->open_file_cache_min_uses;

        if (conf->open_file_cache == NGX_CONF_UNSET_PTR) {
            conf->open_file_cache = NULL;
        }
    }

    if (conf->logs || conf->off) {
        return NGX_CONF_OK;
    }

    conf->logs = prev->logs;
    conf->off = prev->off;

    return NGX_CONF_OK;
}