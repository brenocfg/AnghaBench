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
struct obs_scene_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ apply_scene_item_volume (struct obs_scene_item*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void process_all_audio_actions(struct obs_scene_item *item,
				      size_t sample_rate)
{
	while (apply_scene_item_volume(item, NULL, 0, sample_rate))
		;
}