#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_core_app_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 

__attribute__((used)) static char *
ngx_rtmp_core_merge_app_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_rtmp_core_app_conf_t *prev = parent;
    ngx_rtmp_core_app_conf_t *conf = child;

    (void)prev;
    (void)conf;

    return NGX_CONF_OK;
}