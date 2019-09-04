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
struct obs_video_info {int base_width; int base_height; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_data_set_default_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  obs_get_video_info (struct obs_video_info*) ; 

__attribute__((used)) static void color_source_defaults(obs_data_t *settings)
{
	struct obs_video_info ovi;
	obs_get_video_info(&ovi);

	obs_data_set_default_int(settings, "color", 0xFFFFFFFF);
	obs_data_set_default_int(settings, "width", ovi.base_width);
	obs_data_set_default_int(settings, "height", ovi.base_height);
}