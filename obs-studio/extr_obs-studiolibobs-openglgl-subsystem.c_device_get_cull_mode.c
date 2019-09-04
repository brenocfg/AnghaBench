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
struct TYPE_3__ {int cur_cull_mode; } ;
typedef  TYPE_1__ gs_device_t ;
typedef  enum gs_cull_mode { ____Placeholder_gs_cull_mode } gs_cull_mode ;

/* Variables and functions */

enum gs_cull_mode device_get_cull_mode(const gs_device_t *device)
{
	return device->cur_cull_mode;
}