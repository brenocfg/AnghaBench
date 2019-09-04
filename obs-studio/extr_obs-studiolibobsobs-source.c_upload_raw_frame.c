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
struct obs_source_frame {int /*<<< orphan*/  width; int /*<<< orphan*/ * data; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  full_range; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
#define  CONVERT_420 135 
#define  CONVERT_422_U 134 
#define  CONVERT_422_Y 133 
#define  CONVERT_444 132 
#define  CONVERT_800 131 
#define  CONVERT_NONE 130 
#define  CONVERT_NV12 129 
#define  CONVERT_RGB_LIMITED 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int get_convert_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_set_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void upload_raw_frame(gs_texture_t *tex,
		const struct obs_source_frame *frame)
{
	switch (get_convert_type(frame->format, frame->full_range)) {
		case CONVERT_422_U:
		case CONVERT_422_Y:
		case CONVERT_800:
		case CONVERT_RGB_LIMITED:
			gs_texture_set_image(tex, frame->data[0],
					frame->linesize[0], false);
			break;

		case CONVERT_420:
		case CONVERT_NV12:
		case CONVERT_444:
			gs_texture_set_image(tex, frame->data[0],
					frame->width, false);
			break;

		case CONVERT_NONE:
			assert(false && "No conversion requested");
			break;
	}
}