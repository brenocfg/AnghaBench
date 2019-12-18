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
struct obs_source_frame {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; int /*<<< orphan*/  full_range; int /*<<< orphan*/  format; } ;
typedef  int /*<<< orphan*/  gs_texture_t ;

/* Variables and functions */
#define  CONVERT_420 140 
#define  CONVERT_420_A 139 
#define  CONVERT_422 138 
#define  CONVERT_422_A 137 
#define  CONVERT_422_PACK 136 
#define  CONVERT_444 135 
#define  CONVERT_444_A 134 
#define  CONVERT_444_A_PACK 133 
#define  CONVERT_800 132 
#define  CONVERT_BGR3 131 
#define  CONVERT_NONE 130 
#define  CONVERT_NV12 129 
#define  CONVERT_RGB_LIMITED 128 
 size_t MAX_AV_PLANES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int get_convert_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_texture_set_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void upload_raw_frame(gs_texture_t *tex[MAX_AV_PLANES],
			     const struct obs_source_frame *frame)
{
	switch (get_convert_type(frame->format, frame->full_range)) {
	case CONVERT_422_PACK:
	case CONVERT_800:
	case CONVERT_RGB_LIMITED:
	case CONVERT_BGR3:
	case CONVERT_420:
	case CONVERT_422:
	case CONVERT_NV12:
	case CONVERT_444:
	case CONVERT_420_A:
	case CONVERT_422_A:
	case CONVERT_444_A:
	case CONVERT_444_A_PACK:
		for (size_t c = 0; c < MAX_AV_PLANES; c++) {
			if (tex[c])
				gs_texture_set_image(tex[c], frame->data[c],
						     frame->linesize[c], false);
		}
		break;

	case CONVERT_NONE:
		assert(false && "No conversion requested");
		break;
	}
}