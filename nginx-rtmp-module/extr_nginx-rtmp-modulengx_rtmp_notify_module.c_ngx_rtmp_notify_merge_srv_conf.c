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
typedef  size_t ngx_uint_t ;
struct TYPE_2__ {int /*<<< orphan*/  method; int /*<<< orphan*/ * url; } ;
typedef  TYPE_1__ ngx_rtmp_notify_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  NGX_RTMP_NETCALL_HTTP_POST ; 
 size_t NGX_RTMP_NOTIFY_SRV_MAX ; 
 int /*<<< orphan*/  ngx_conf_merge_ptr_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_conf_merge_uint_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_rtmp_notify_merge_srv_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_rtmp_notify_srv_conf_t *prev = parent;
    ngx_rtmp_notify_srv_conf_t *conf = child;
    ngx_uint_t                  n;

    for (n = 0; n < NGX_RTMP_NOTIFY_SRV_MAX; ++n) {
        ngx_conf_merge_ptr_value(conf->url[n], prev->url[n], NULL);
    }

    ngx_conf_merge_uint_value(conf->method, prev->method,
                              NGX_RTMP_NETCALL_HTTP_POST);

    return NGX_CONF_OK;
}