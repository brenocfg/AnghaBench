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
struct vpfe_video_device {struct vpfe_device* vpfe_dev; struct vpfe_ext_subdev_info* current_ext_subdev; } ;
struct vpfe_ext_subdev_info {size_t num_inputs; int /*<<< orphan*/ * inputs; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct v4l2_input {size_t index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memcpy (struct v4l2_input*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpfe_enum_input(struct file *file, void *priv,
				 struct v4l2_input *inp)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_ext_subdev_info *sdinfo = video->current_ext_subdev;
	struct vpfe_device *vpfe_dev = video->vpfe_dev;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_enum_input\n");
	/* enumerate from the subdev user has chosen through mc */
	if (inp->index < sdinfo->num_inputs) {
		memcpy(inp, &sdinfo->inputs[inp->index],
		       sizeof(struct v4l2_input));
		return 0;
	}
	return -EINVAL;
}