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
struct skeleton {int /*<<< orphan*/  std; scalar_t__ input; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 struct skeleton* video_drvdata (struct file*) ; 

__attribute__((used)) static int skeleton_g_std(struct file *file, void *priv, v4l2_std_id *std)
{
	struct skeleton *skel = video_drvdata(file);

	/* G_STD is not supported on the HDMI input */
	if (skel->input)
		return -ENODATA;

	*std = skel->std;
	return 0;
}