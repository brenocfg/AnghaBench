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
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_3__ {scalar_t__ degrade; } ;
typedef  TYPE_1__ ngx_http_degradation_loc_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 int /*<<< orphan*/  ngx_http_degradation_module ; 
 scalar_t__ ngx_http_degraded (int /*<<< orphan*/ *) ; 
 TYPE_1__* ngx_http_get_module_loc_conf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_degradation_handler(ngx_http_request_t *r)
{
    ngx_http_degradation_loc_conf_t  *dlcf;

    dlcf = ngx_http_get_module_loc_conf(r, ngx_http_degradation_module);

    if (dlcf->degrade && ngx_http_degraded(r)) {
        return dlcf->degrade;
    }

    return NGX_DECLINED;
}