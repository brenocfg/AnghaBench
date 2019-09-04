#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ intl_end; int bandwidth; int intl_bytes; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ ngx_rtmp_bandwidth_t ;
struct TYPE_5__ {scalar_t__ sec; } ;

/* Variables and functions */
 int NGX_RTMP_BANDWIDTH_INTERVAL ; 
 TYPE_3__* ngx_cached_time ; 

void
ngx_rtmp_update_bandwidth(ngx_rtmp_bandwidth_t *bw, uint32_t bytes)
{
    if (ngx_cached_time->sec > bw->intl_end) {
        bw->bandwidth = ngx_cached_time->sec >
            bw->intl_end + NGX_RTMP_BANDWIDTH_INTERVAL
            ? 0
            : bw->intl_bytes / NGX_RTMP_BANDWIDTH_INTERVAL;
        bw->intl_bytes = 0;
        bw->intl_end = ngx_cached_time->sec + NGX_RTMP_BANDWIDTH_INTERVAL;
    }

    bw->bytes += bytes;
    bw->intl_bytes += bytes;
}