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
struct v4l2_fmtdesc {int flags; scalar_t__ index; int /*<<< orphan*/  pixelformat; scalar_t__ description; int /*<<< orphan*/  type; } ;
struct dstr {int /*<<< orphan*/  array; } ;
typedef  int /*<<< orphan*/  obs_property_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_FMT_FLAG_EMULATED ; 
 scalar_t__ VIDEO_FORMAT_NONE ; 
 int /*<<< orphan*/  VIDIOC_ENUM_FMT ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_cat (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  obs_property_list_add_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_property_list_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_ioctl (int,int /*<<< orphan*/ ,struct v4l2_fmtdesc*) ; 
 scalar_t__ v4l2_to_obs_video_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4l2_format_list(int dev, obs_property_t *prop)
{
	struct v4l2_fmtdesc fmt;
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.index = 0;
	struct dstr buffer;
	dstr_init(&buffer);

	obs_property_list_clear(prop);

	while (v4l2_ioctl(dev, VIDIOC_ENUM_FMT, &fmt) == 0) {
		dstr_copy(&buffer, (char *)fmt.description);
		if (fmt.flags & V4L2_FMT_FLAG_EMULATED)
			dstr_cat(&buffer, " (Emulated)");

		if (v4l2_to_obs_video_format(fmt.pixelformat) !=
		    VIDEO_FORMAT_NONE) {
			obs_property_list_add_int(prop, buffer.array,
						  fmt.pixelformat);
			blog(LOG_INFO, "Pixelformat: %s (available)",
			     buffer.array);
		} else {
			blog(LOG_INFO, "Pixelformat: %s (unavailable)",
			     buffer.array);
		}
		fmt.index++;
	}

	dstr_free(&buffer);
}