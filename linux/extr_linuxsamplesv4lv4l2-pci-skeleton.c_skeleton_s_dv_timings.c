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
struct v4l2_dv_timings {int dummy; } ;
struct skeleton {scalar_t__ input; int /*<<< orphan*/  format; struct v4l2_dv_timings timings; int /*<<< orphan*/  queue; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODATA ; 
 int /*<<< orphan*/  skel_timings_cap ; 
 int /*<<< orphan*/  skeleton_fill_pix_format (struct skeleton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_find_dv_timings_cap (struct v4l2_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_match_dv_timings (struct v4l2_dv_timings*,struct v4l2_dv_timings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_valid_dv_timings (struct v4l2_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct skeleton* video_drvdata (struct file*) ; 

__attribute__((used)) static int skeleton_s_dv_timings(struct file *file, void *_fh,
				 struct v4l2_dv_timings *timings)
{
	struct skeleton *skel = video_drvdata(file);

	/* S_DV_TIMINGS is not supported on the S-Video input */
	if (skel->input == 0)
		return -ENODATA;

	/* Quick sanity check */
	if (!v4l2_valid_dv_timings(timings, &skel_timings_cap, NULL, NULL))
		return -EINVAL;

	/* Check if the timings are part of the CEA-861 timings. */
	if (!v4l2_find_dv_timings_cap(timings, &skel_timings_cap,
				      0, NULL, NULL))
		return -EINVAL;

	/* Return 0 if the new timings are the same as the current timings. */
	if (v4l2_match_dv_timings(timings, &skel->timings, 0, false))
		return 0;

	/*
	 * Changing the timings implies a format change, which is not allowed
	 * while buffers for use with streaming have already been allocated.
	 */
	if (vb2_is_busy(&skel->queue))
		return -EBUSY;

	/* TODO: Configure new timings */

	/* Save timings */
	skel->timings = *timings;

	/* Update the internal format */
	skeleton_fill_pix_format(skel, &skel->format);
	return 0;
}