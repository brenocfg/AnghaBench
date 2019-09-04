#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vpfe_video_device {TYPE_3__* current_ext_subdev; struct vpfe_device* vpfe_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pads; } ;
struct vpfe_device {int num_ext_subdevs; TYPE_4__** sd; TYPE_2__* pdev; TYPE_1__ vpfe_isif; } ;
struct vpfe_config {int num_subdevs; TYPE_3__* sub_devs; } ;
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct media_pad {int /*<<< orphan*/  entity; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_4__* subdev; int /*<<< orphan*/  module_name; } ;
struct TYPE_6__ {struct vpfe_config* platform_data; } ;

/* Variables and functions */
 int EINVAL ; 
 struct media_pad* media_entity_remote_pad (int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_update_current_ext_subdev(struct vpfe_video_device *video)
{
	struct vpfe_device *vpfe_dev = video->vpfe_dev;
	struct vpfe_config *vpfe_cfg;
	struct v4l2_subdev *subdev;
	struct media_pad *remote;
	int i;

	remote = media_entity_remote_pad(&vpfe_dev->vpfe_isif.pads[0]);
	if (!remote) {
		pr_err("Invalid media connection to isif/ccdc\n");
		return -EINVAL;
	}

	subdev = media_entity_to_v4l2_subdev(remote->entity);
	vpfe_cfg = vpfe_dev->pdev->platform_data;
	for (i = 0; i < vpfe_cfg->num_subdevs; i++) {
		if (!strcmp(vpfe_cfg->sub_devs[i].module_name, subdev->name)) {
			video->current_ext_subdev = &vpfe_cfg->sub_devs[i];
			break;
		}
	}

	/* if user not linked decoder/sensor to isif/ccdc */
	if (i == vpfe_cfg->num_subdevs) {
		pr_err("Invalid media chain connection to isif/ccdc\n");
		return -EINVAL;
	}
	/* find the v4l2 subdev pointer */
	for (i = 0; i < vpfe_dev->num_ext_subdevs; i++) {
		if (!strcmp(video->current_ext_subdev->module_name,
			vpfe_dev->sd[i]->name))
			video->current_ext_subdev->subdev = vpfe_dev->sd[i];
	}
	return 0;
}