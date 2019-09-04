#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bm2835_mmal_dev {int /*<<< orphan*/  v4l2_dev; scalar_t__* ctrls; } ;
struct TYPE_3__ {int (* setter ) (struct bm2835_mmal_dev*,scalar_t__,TYPE_1__*) ;int /*<<< orphan*/  ignore_errors; } ;

/* Variables and functions */
 int V4L2_CTRL_COUNT ; 
 int /*<<< orphan*/  bcm2835_v4l2_debug ; 
 int stub1 (struct bm2835_mmal_dev*,scalar_t__,TYPE_1__*) ; 
 TYPE_1__* v4l2_ctrls ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

int bm2835_mmal_set_all_camera_controls(struct bm2835_mmal_dev *dev)
{
	int c;
	int ret = 0;

	for (c = 0; c < V4L2_CTRL_COUNT; c++) {
		if ((dev->ctrls[c]) && (v4l2_ctrls[c].setter)) {
			ret = v4l2_ctrls[c].setter(dev, dev->ctrls[c],
						   &v4l2_ctrls[c]);
			if (!v4l2_ctrls[c].ignore_errors && ret) {
				v4l2_dbg(1, bcm2835_v4l2_debug, &dev->v4l2_dev,
					 "Failed when setting default values for ctrl %d\n",
					 c);
				break;
			}
		}
	}
	return ret;
}