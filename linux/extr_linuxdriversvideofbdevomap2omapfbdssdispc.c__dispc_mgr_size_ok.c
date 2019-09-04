#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_4__ {TYPE_1__* feat; } ;
struct TYPE_3__ {scalar_t__ mgr_width_max; scalar_t__ mgr_height_max; } ;

/* Variables and functions */
 TYPE_2__ dispc ; 

__attribute__((used)) static bool _dispc_mgr_size_ok(u16 width, u16 height)
{
	return width <= dispc.feat->mgr_width_max &&
		height <= dispc.feat->mgr_height_max;
}