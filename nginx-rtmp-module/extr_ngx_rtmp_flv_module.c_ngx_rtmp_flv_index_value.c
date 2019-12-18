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

/* Variables and functions */
 int /*<<< orphan*/  ngx_rtmp_rmemcpy (double*,void*,int) ; 

__attribute__((used)) static double
ngx_rtmp_flv_index_value(void *src)
{
    double      v;

    ngx_rtmp_rmemcpy(&v, src, 8);

    return v;
}