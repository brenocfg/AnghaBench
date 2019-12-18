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
typedef  scalar_t__ uint32_t ;
struct obs_scene_item {scalar_t__ last_width; scalar_t__ last_height; int /*<<< orphan*/  source; } ;

/* Variables and functions */
 scalar_t__ obs_source_get_height (int /*<<< orphan*/ ) ; 
 scalar_t__ obs_source_get_width (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool source_size_changed(struct obs_scene_item *item)
{
	uint32_t width = obs_source_get_width(item->source);
	uint32_t height = obs_source_get_height(item->source);

	return item->last_width != width || item->last_height != height;
}