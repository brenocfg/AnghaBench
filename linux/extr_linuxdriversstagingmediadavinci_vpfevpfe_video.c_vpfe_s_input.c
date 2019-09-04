#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  tvnorms; } ;
struct vpfe_video_device {unsigned int current_input; int /*<<< orphan*/  lock; TYPE_2__ video_dev; struct vpfe_ext_subdev_info* current_ext_subdev; scalar_t__ started; struct vpfe_device* vpfe_dev; } ;
struct vpfe_route {int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;
struct vpfe_ext_subdev_info {int num_inputs; struct v4l2_input* inputs; int /*<<< orphan*/  grp_id; scalar_t__ can_route; struct vpfe_route* routes; int /*<<< orphan*/  module_name; int /*<<< orphan*/  registered; } ;
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; TYPE_1__* cfg; } ;
struct v4l2_input {int /*<<< orphan*/  std; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ (* setup_input ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  debug ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_routing ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int v4l2_device_call_until_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vpfe_video_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vpfe_video_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vpfe_s_input(struct file *file, void *priv, unsigned int index)
{
	struct vpfe_video_device *video = video_drvdata(file);
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct vpfe_ext_subdev_info *sdinfo;
	struct vpfe_route *route;
	struct v4l2_input *inps;
	u32 output;
	u32 input;
	int ret;
	int i;

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_s_input\n");

	ret = mutex_lock_interruptible(&video->lock);
	if (ret)
		return ret;
	/*
	 * If streaming is started return device busy
	 * error
	 */
	if (video->started) {
		v4l2_err(&vpfe_dev->v4l2_dev, "Streaming is on\n");
		ret = -EBUSY;
		goto unlock_out;
	}

	sdinfo = video->current_ext_subdev;
	if (!sdinfo->registered) {
		ret = -EINVAL;
		goto unlock_out;
	}
	if (vpfe_dev->cfg->setup_input &&
		vpfe_dev->cfg->setup_input(sdinfo->grp_id) < 0) {
		ret = -EFAULT;
		v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev,
			  "couldn't setup input for %s\n",
			  sdinfo->module_name);
		goto unlock_out;
	}
	route = &sdinfo->routes[index];
	if (route && sdinfo->can_route) {
		input = route->input;
		output = route->output;
		ret = v4l2_device_call_until_err(&vpfe_dev->v4l2_dev,
						 sdinfo->grp_id, video,
						 s_routing, input, output, 0);
		if (ret) {
			v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev,
				"s_input:error in setting input in decoder\n");
			ret = -EINVAL;
			goto unlock_out;
		}
	}
	/* set standards set by subdev in video device */
	for (i = 0; i < sdinfo->num_inputs; i++) {
		inps = &sdinfo->inputs[i];
		video->video_dev.tvnorms |= inps->std;
	}
	video->current_input = index;
unlock_out:
	mutex_unlock(&video->lock);
	return ret;
}