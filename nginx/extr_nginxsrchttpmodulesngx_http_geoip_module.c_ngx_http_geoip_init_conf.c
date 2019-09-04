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
struct TYPE_2__ {int /*<<< orphan*/  proxy_recursive; } ;
typedef  TYPE_1__ ngx_http_geoip_conf_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 char* NGX_CONF_OK ; 
 int /*<<< orphan*/  ngx_conf_init_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
ngx_http_geoip_init_conf(ngx_conf_t *cf, void *conf)
{
    ngx_http_geoip_conf_t  *gcf = conf;

    ngx_conf_init_value(gcf->proxy_recursive, 0);

    return NGX_CONF_OK;
}