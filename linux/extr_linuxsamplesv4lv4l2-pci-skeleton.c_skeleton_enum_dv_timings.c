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
struct v4l2_enum_dv_timings {int dummy; } ;
struct skeleton {scalar_t__ input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  skel_timings_cap ; 
 int v4l2_enum_dv_timings_cap (struct v4l2_enum_dv_timings*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct skeleton* video_drvdata (struct file*) ; 

__attribute__((used)) static int skeleton_enum_dv_timings(struct file *file, void *_fh,
				    struct v4l2_enum_dv_timings *timings)
{
	struct skeleton *skel = video_drvdata(file);

	/* ENUM_DV_TIMINGS is not supported on the S-Video input */
	if (skel->input == 0)
		return -ENODATA;

	return v4l2_enum_dv_timings_cap(timings, &skel_timings_cap,
					NULL, NULL);
}