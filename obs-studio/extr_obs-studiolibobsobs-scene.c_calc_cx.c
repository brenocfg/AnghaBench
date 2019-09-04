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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ left; scalar_t__ right; } ;
struct obs_scene_item {TYPE_1__ crop; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t calc_cx(const struct obs_scene_item *item,
		uint32_t width)
{
	uint32_t crop_cx = item->crop.left + item->crop.right;
	return (crop_cx > width) ? 2 : (width - crop_cx);
}