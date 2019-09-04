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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;
struct TYPE_2__ {int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_1__* ngx_cached_time ; 
 int /*<<< orphan*/  start_time ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_stat_postconfiguration(ngx_conf_t *cf)
{
    start_time = ngx_cached_time->sec;

    return NGX_OK;
}