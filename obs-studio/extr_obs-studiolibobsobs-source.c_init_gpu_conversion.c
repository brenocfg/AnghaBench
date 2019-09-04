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
struct obs_source_frame {int /*<<< orphan*/  full_range; int /*<<< orphan*/  format; } ;
struct obs_source {int dummy; } ;

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
 int set_nv12_sizes (struct obs_source*,struct obs_source_frame const*) ; 
 int set_packed422_sizes (struct obs_source*,struct obs_source_frame const*) ; 
 int set_planar420_sizes (struct obs_source*,struct obs_source_frame const*) ; 
 int set_planar444_sizes (struct obs_source*,struct obs_source_frame const*) ; 
 int set_rgb_limited_sizes (struct obs_source*,struct obs_source_frame const*) ; 
 int set_y800_sizes (struct obs_source*,struct obs_source_frame const*) ; 

__attribute__((used)) static inline bool init_gpu_conversion(struct obs_source *source,
		const struct obs_source_frame *frame)
{
	switch (get_convert_type(frame->format, frame->full_range)) {
		case CONVERT_422_Y:
		case CONVERT_422_U:
			return set_packed422_sizes(source, frame);

		case CONVERT_420:
			return set_planar420_sizes(source, frame);

		case CONVERT_NV12:
			return set_nv12_sizes(source, frame);

		case CONVERT_444:
			return set_planar444_sizes(source, frame);

		case CONVERT_800:
			return set_y800_sizes(source, frame);

		case CONVERT_RGB_LIMITED:
			return set_rgb_limited_sizes(source, frame);

		case CONVERT_NONE:
			assert(false && "No conversion requested");
			break;

	}
	return false;
}