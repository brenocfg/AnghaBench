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
struct obs_core_video {int texture_rendered; int texture_converted; scalar_t__ cur_texture; int /*<<< orphan*/  vframe_info_buffer; } ;
struct TYPE_2__ {struct obs_core_video video; } ;

/* Variables and functions */
 int /*<<< orphan*/  circlebuf_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* obs ; 

__attribute__((used)) static void clear_base_frame_data(void)
{
	struct obs_core_video *video = &obs->video;
	video->texture_rendered = false;
	video->texture_converted = false;
	circlebuf_free(&video->vframe_info_buffer);
	video->cur_texture = 0;
}