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
typedef  scalar_t__ v4l2_std_id ;
struct skeleton {scalar_t__ std; int /*<<< orphan*/  format; int /*<<< orphan*/  queue; scalar_t__ input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODATA ; 
 int /*<<< orphan*/  skeleton_fill_pix_format (struct skeleton*,int /*<<< orphan*/ *) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct skeleton* video_drvdata (struct file*) ; 

__attribute__((used)) static int skeleton_s_std(struct file *file, void *priv, v4l2_std_id std)
{
	struct skeleton *skel = video_drvdata(file);

	/* S_STD is not supported on the HDMI input */
	if (skel->input)
		return -ENODATA;

	/*
	 * No change, so just return. Some applications call S_STD again after
	 * the buffers for streaming have been set up, so we have to allow for
	 * this behavior.
	 */
	if (std == skel->std)
		return 0;

	/*
	 * Changing the standard implies a format change, which is not allowed
	 * while buffers for use with streaming have already been allocated.
	 */
	if (vb2_is_busy(&skel->queue))
		return -EBUSY;

	/* TODO: handle changing std */

	skel->std = std;

	/* Update the internal format */
	skeleton_fill_pix_format(skel, &skel->format);
	return 0;
}