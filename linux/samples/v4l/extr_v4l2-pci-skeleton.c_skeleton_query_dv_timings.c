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
struct v4l2_dv_timings {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct skeleton {scalar_t__ input; TYPE_1__ v4l2_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENOLCK ; 
 int ENOLINK ; 
 int ERANGE ; 
 scalar_t__ cannot_lock_to_signal ; 
 int /*<<< orphan*/  detect_timings () ; 
 scalar_t__ no_signal ; 
 scalar_t__ signal_out_of_range_of_capabilities ; 
 int /*<<< orphan*/  v4l2_print_dv_timings (int /*<<< orphan*/ ,char*,struct v4l2_dv_timings*,int) ; 
 struct skeleton* video_drvdata (struct file*) ; 

__attribute__((used)) static int skeleton_query_dv_timings(struct file *file, void *_fh,
				     struct v4l2_dv_timings *timings)
{
	struct skeleton *skel = video_drvdata(file);

	/* QUERY_DV_TIMINGS is not supported on the S-Video input */
	if (skel->input == 0)
		return -ENODATA;

#ifdef TODO
	/*
	 * Query currently seen timings. This function should look
	 * something like this:
	 */
	detect_timings();
	if (no_signal)
		return -ENOLINK;
	if (cannot_lock_to_signal)
		return -ENOLCK;
	if (signal_out_of_range_of_capabilities)
		return -ERANGE;

	/* Useful for debugging */
	v4l2_print_dv_timings(skel->v4l2_dev.name, "query_dv_timings:",
			timings, true);
#endif
	return 0;
}