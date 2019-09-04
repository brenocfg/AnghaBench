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
struct capture_priv {int /*<<< orphan*/  src_sd; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  s_std ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video ; 
 struct capture_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int capture_s_std(struct file *file, void *fh, v4l2_std_id std)
{
	struct capture_priv *priv = video_drvdata(file);

	if (vb2_is_busy(&priv->q))
		return -EBUSY;

	return v4l2_subdev_call(priv->src_sd, video, s_std, std);
}