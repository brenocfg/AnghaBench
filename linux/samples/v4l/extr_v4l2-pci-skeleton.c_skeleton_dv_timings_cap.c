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
struct v4l2_dv_timings_cap {int dummy; } ;
struct skeleton {scalar_t__ input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 struct v4l2_dv_timings_cap skel_timings_cap ; 
 struct skeleton* video_drvdata (struct file*) ; 

__attribute__((used)) static int skeleton_dv_timings_cap(struct file *file, void *fh,
				   struct v4l2_dv_timings_cap *cap)
{
	struct skeleton *skel = video_drvdata(file);

	/* DV_TIMINGS_CAP is not supported on the S-Video input */
	if (skel->input == 0)
		return -ENODATA;
	*cap = skel_timings_cap;
	return 0;
}