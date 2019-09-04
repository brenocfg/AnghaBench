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
struct TYPE_2__ {scalar_t__ bind; scalar_t__ wildcard; } ;
typedef  TYPE_1__ ngx_rtmp_conf_addr_t ;
typedef  int ngx_int_t ;

/* Variables and functions */

__attribute__((used)) static ngx_int_t
ngx_rtmp_cmp_conf_addrs(const void *one, const void *two)
{
    ngx_rtmp_conf_addr_t  *first, *second;

    first = (ngx_rtmp_conf_addr_t *) one;
    second = (ngx_rtmp_conf_addr_t *) two;

    if (first->wildcard) {
        /* a wildcard must be the last resort, shift it to the end */
        return 1;
    }

    if (first->bind && !second->bind) {
        /* shift explicit bind()ed addresses to the start */
        return -1;
    }

    if (!first->bind && second->bind) {
        /* shift explicit bind()ed addresses to the start */
        return 1;
    }

    /* do not sort by default */

    return 0;
}