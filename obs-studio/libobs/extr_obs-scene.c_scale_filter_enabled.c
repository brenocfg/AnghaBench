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
struct obs_scene_item {scalar_t__ scale_filter; } ;

/* Variables and functions */
 scalar_t__ OBS_SCALE_DISABLE ; 

__attribute__((used)) static inline bool scale_filter_enabled(const struct obs_scene_item *item)
{
	return item->scale_filter != OBS_SCALE_DISABLE;
}