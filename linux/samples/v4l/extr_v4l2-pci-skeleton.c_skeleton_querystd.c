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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct skeleton {scalar_t__ input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  V4L2_STD_525_60 ; 
 int /*<<< orphan*/  V4L2_STD_625_50 ; 
 int /*<<< orphan*/  get_signal_info () ; 
 scalar_t__ no_signal ; 
 scalar_t__ signal_has_525_lines ; 
 struct skeleton* video_drvdata (struct file*) ; 

__attribute__((used)) static int skeleton_querystd(struct file *file, void *priv, v4l2_std_id *std)
{
	struct skeleton *skel = video_drvdata(file);

	/* QUERY_STD is not supported on the HDMI input */
	if (skel->input)
		return -ENODATA;

#ifdef TODO
	/*
	 * Query currently seen standard. Initial value of *std is
	 * V4L2_STD_ALL. This function should look something like this:
	 */
	get_signal_info();
	if (no_signal) {
		*std = 0;
		return 0;
	}
	/* Use signal information to reduce the number of possible standards */
	if (signal_has_525_lines)
		*std &= V4L2_STD_525_60;
	else
		*std &= V4L2_STD_625_50;
#endif
	return 0;
}