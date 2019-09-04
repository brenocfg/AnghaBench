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
struct TYPE_2__ {int /*<<< orphan*/  tvnorms; } ;
struct skeleton {unsigned int input; int /*<<< orphan*/  format; TYPE_1__ vdev; int /*<<< orphan*/  queue; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  SKEL_TVNORMS ; 
 int /*<<< orphan*/  skeleton_fill_pix_format (struct skeleton*,int /*<<< orphan*/ *) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct skeleton* video_drvdata (struct file*) ; 

__attribute__((used)) static int skeleton_s_input(struct file *file, void *priv, unsigned int i)
{
	struct skeleton *skel = video_drvdata(file);

	if (i > 1)
		return -EINVAL;

	/*
	 * Changing the input implies a format change, which is not allowed
	 * while buffers for use with streaming have already been allocated.
	 */
	if (vb2_is_busy(&skel->queue))
		return -EBUSY;

	skel->input = i;
	/*
	 * Update tvnorms. The tvnorms value is used by the core to implement
	 * VIDIOC_ENUMSTD so it has to be correct. If tvnorms == 0, then
	 * ENUMSTD will return -ENODATA.
	 */
	skel->vdev.tvnorms = i ? 0 : SKEL_TVNORMS;

	/* Update the internal format */
	skeleton_fill_pix_format(skel, &skel->format);
	return 0;
}