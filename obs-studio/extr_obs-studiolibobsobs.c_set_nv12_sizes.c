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
typedef  int uint32_t ;
struct obs_video_info {int output_width; int output_height; } ;
struct obs_core_video {int* plane_offsets; int* plane_linewidth; int* plane_sizes; int conversion_height; char* conversion_tech; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 void* GET_ALIGN (int,int) ; 
 int PIXEL_SIZE ; 
 TYPE_1__* obs ; 

__attribute__((used)) static inline void set_nv12_sizes(const struct obs_video_info *ovi)
{
	struct obs_core_video *video = &obs->video;
	uint32_t chroma_pixels;
	uint32_t total_bytes;

	chroma_pixels = (ovi->output_width * ovi->output_height / 2);
	chroma_pixels = GET_ALIGN(chroma_pixels, PIXEL_SIZE);

	video->plane_offsets[0] = 0;
	video->plane_offsets[1] = ovi->output_width * ovi->output_height;

	video->plane_linewidth[0] = ovi->output_width;
	video->plane_linewidth[1] = ovi->output_width;

	video->plane_sizes[0] = video->plane_offsets[1];
	video->plane_sizes[1] = video->plane_sizes[0]/2;

	total_bytes = video->plane_offsets[1] + chroma_pixels;

	video->conversion_height =
		(total_bytes/PIXEL_SIZE + ovi->output_width-1) /
		ovi->output_width;

	video->conversion_height = GET_ALIGN(video->conversion_height, 2);
	video->conversion_tech = "NV12";
}