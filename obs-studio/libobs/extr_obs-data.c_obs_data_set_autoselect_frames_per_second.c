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
struct media_frames_per_second {int dummy; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  make_frames_per_second (struct media_frames_per_second,char const*) ; 
 int /*<<< orphan*/  obs_take_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_item_auto ; 

void obs_data_set_autoselect_frames_per_second(
	obs_data_t *data, const char *name, struct media_frames_per_second fps,
	const char *option)
{
	obs_take_obj(data, NULL, name, make_frames_per_second(fps, option),
		     set_item_auto);
}