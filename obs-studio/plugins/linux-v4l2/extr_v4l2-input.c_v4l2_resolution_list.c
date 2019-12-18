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
typedef  int /*<<< orphan*/  uint_fast32_t ;
struct TYPE_2__ {int width; int height; } ;
struct v4l2_frmsizeenum {int type; scalar_t__ index; TYPE_1__ discrete; int /*<<< orphan*/  pixel_format; } ;
struct dstr {int /*<<< orphan*/  array; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
#define  V4L2_FRMSIZE_TYPE_DISCRETE 128 
 int /*<<< orphan*/  VIDIOC_ENUM_FRAMESIZES ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,int,int) ; 
 int /*<<< orphan*/  obs_module_text (char*) ; 
 int /*<<< orphan*/  obs_property_list_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  obs_property_list_clear (int /*<<< orphan*/ *) ; 
 int* v4l2_framesizes ; 
 int /*<<< orphan*/  v4l2_ioctl (int,int /*<<< orphan*/ ,struct v4l2_frmsizeenum*) ; 
 int const v4l2_pack_tuple (int,int) ; 
 int /*<<< orphan*/  v4l2_unpack_tuple (int*,int*,int const) ; 

__attribute__((used)) static void v4l2_resolution_list(int dev, uint_fast32_t pixelformat,
				 obs_property_t *prop)
{
	struct v4l2_frmsizeenum frmsize;
	frmsize.pixel_format = pixelformat;
	frmsize.index = 0;
	struct dstr buffer;
	dstr_init(&buffer);

	obs_property_list_clear(prop);

	obs_property_list_add_int(prop, obs_module_text("LeaveUnchanged"), -1);

	v4l2_ioctl(dev, VIDIOC_ENUM_FRAMESIZES, &frmsize);

	switch (frmsize.type) {
	case V4L2_FRMSIZE_TYPE_DISCRETE:
		while (v4l2_ioctl(dev, VIDIOC_ENUM_FRAMESIZES, &frmsize) == 0) {
			dstr_printf(&buffer, "%dx%d", frmsize.discrete.width,
				    frmsize.discrete.height);
			obs_property_list_add_int(
				prop, buffer.array,
				v4l2_pack_tuple(frmsize.discrete.width,
						frmsize.discrete.height));
			frmsize.index++;
		}
		break;
	default:
		blog(LOG_INFO, "Stepwise and Continuous framesizes "
			       "are currently hardcoded");

		for (const int *packed = v4l2_framesizes; *packed; ++packed) {
			int width;
			int height;
			v4l2_unpack_tuple(&width, &height, *packed);
			dstr_printf(&buffer, "%dx%d", width, height);
			obs_property_list_add_int(prop, buffer.array, *packed);
		}
		break;
	}

	dstr_free(&buffer);
}