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
typedef  int /*<<< orphan*/  uint8_t ;
struct ffmpeg_mux {int /*<<< orphan*/ * audio_header; int /*<<< orphan*/  video_header; } ;
struct ffm_packet_info {scalar_t__ type; size_t index; scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ FFM_PACKET_VIDEO ; 
 int /*<<< orphan*/  set_header (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void ffmpeg_mux_header(struct ffmpeg_mux *ffm, uint8_t *data,
			      struct ffm_packet_info *info)
{
	if (info->type == FFM_PACKET_VIDEO) {
		set_header(&ffm->video_header, data, (size_t)info->size);
	} else {
		set_header(&ffm->audio_header[info->index], data,
			   (size_t)info->size);
	}
}