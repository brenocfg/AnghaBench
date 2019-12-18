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
struct TYPE_2__ {int /*<<< orphan*/  rules6; int /*<<< orphan*/  rules; } ;
typedef  TYPE_1__ ngx_rtmp_access_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_rtmp_access_merge_rules (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
ngx_rtmp_access_merge_app_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_rtmp_access_app_conf_t *prev = parent;
    ngx_rtmp_access_app_conf_t *conf = child;

    if (ngx_rtmp_access_merge_rules(&prev->rules, &conf->rules) != NGX_OK) {
        return NGX_CONF_ERROR;
    }

#if (NGX_HAVE_INET6)
    if (ngx_rtmp_access_merge_rules(&prev->rules6, &conf->rules6) != NGX_OK) {
        return NGX_CONF_ERROR;
    }
#endif

    return NGX_CONF_OK;
}