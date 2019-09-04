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
struct video_output_info {char* name; int cache_size; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  range; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  fps_den; int /*<<< orphan*/  fps_num; int /*<<< orphan*/  format; } ;
struct obs_video_info {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  range; int /*<<< orphan*/  output_height; int /*<<< orphan*/  output_width; int /*<<< orphan*/  fps_den; int /*<<< orphan*/  fps_num; int /*<<< orphan*/  output_format; } ;

/* Variables and functions */

__attribute__((used)) static inline void make_video_info(struct video_output_info *vi,
		struct obs_video_info *ovi)
{
	vi->name    = "video";
	vi->format  = ovi->output_format;
	vi->fps_num = ovi->fps_num;
	vi->fps_den = ovi->fps_den;
	vi->width   = ovi->output_width;
	vi->height  = ovi->output_height;
	vi->range   = ovi->range;
	vi->colorspace = ovi->colorspace;
	vi->cache_size = 6;
}