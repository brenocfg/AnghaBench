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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {scalar_t__ pad; size_t index; void* code; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 int EINVAL ; 
 scalar_t__ RESIZER_PAD_SINK ; 
 scalar_t__ RESIZER_PAD_SOURCE ; 
 void** resizer_input_formats ; 
 void** resizer_output_formats ; 

__attribute__((used)) static int resizer_enum_mbus_code(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_mbus_code_enum *code)
{
	if (code->pad == RESIZER_PAD_SINK) {
		if (code->index >= ARRAY_SIZE(resizer_input_formats))
			return -EINVAL;

		code->code = resizer_input_formats[code->index];
	} else if (code->pad == RESIZER_PAD_SOURCE) {
		if (code->index >= ARRAY_SIZE(resizer_output_formats))
			return -EINVAL;

		code->code = resizer_output_formats[code->index];
	}

	return 0;
}