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
struct TYPE_2__ {scalar_t__ city; scalar_t__ org; scalar_t__ country; } ;
typedef  TYPE_1__ ngx_http_geoip_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  GeoIP_delete (scalar_t__) ; 

__attribute__((used)) static void
ngx_http_geoip_cleanup(void *data)
{
    ngx_http_geoip_conf_t  *gcf = data;

    if (gcf->country) {
        GeoIP_delete(gcf->country);
    }

    if (gcf->org) {
        GeoIP_delete(gcf->org);
    }

    if (gcf->city) {
        GeoIP_delete(gcf->city);
    }
}