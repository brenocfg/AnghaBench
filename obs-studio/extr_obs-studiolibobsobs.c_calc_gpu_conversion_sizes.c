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
typedef  int /*<<< orphan*/  uint32_t ;
struct obs_video_info {int /*<<< orphan*/  output_format; } ;
struct TYPE_3__ {int /*<<< orphan*/  plane_linewidth; int /*<<< orphan*/  plane_sizes; int /*<<< orphan*/  plane_offsets; scalar_t__ conversion_height; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
#define  VIDEO_FORMAT_I420 130 
#define  VIDEO_FORMAT_I444 129 
#define  VIDEO_FORMAT_NV12 128 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* obs ; 
 int /*<<< orphan*/  set_420p_sizes (struct obs_video_info const*) ; 
 int /*<<< orphan*/  set_444p_sizes (struct obs_video_info const*) ; 
 int /*<<< orphan*/  set_nv12_sizes (struct obs_video_info const*) ; 

__attribute__((used)) static inline void calc_gpu_conversion_sizes(const struct obs_video_info *ovi)
{
	obs->video.conversion_height = 0;
	memset(obs->video.plane_offsets, 0, sizeof(obs->video.plane_offsets));
	memset(obs->video.plane_sizes, 0, sizeof(obs->video.plane_sizes));
	memset(obs->video.plane_linewidth, 0,
		sizeof(obs->video.plane_linewidth));

	switch ((uint32_t)ovi->output_format) {
	case VIDEO_FORMAT_I420:
		set_420p_sizes(ovi);
		break;
	case VIDEO_FORMAT_NV12:
		set_nv12_sizes(ovi);
		break;
	case VIDEO_FORMAT_I444:
		set_444p_sizes(ovi);
		break;
	}
}