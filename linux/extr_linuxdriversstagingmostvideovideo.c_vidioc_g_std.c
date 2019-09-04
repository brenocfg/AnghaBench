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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 

__attribute__((used)) static int vidioc_g_std(struct file *file, void *priv, v4l2_std_id *norm)
{
	*norm = V4L2_STD_UNKNOWN;
	return 0;
}