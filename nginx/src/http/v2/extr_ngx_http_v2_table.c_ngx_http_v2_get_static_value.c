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
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 TYPE_1__* ngx_http_v2_static_table ; 

ngx_str_t *
ngx_http_v2_get_static_value(ngx_uint_t index)
{
    return &ngx_http_v2_static_table[index - 1].value;
}