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
struct TYPE_2__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; } ;
struct media_entity {int /*<<< orphan*/ * ops; } ;
struct v4l2_subdev {int grp_id; int flags; int /*<<< orphan*/ * ctrl_handler; int /*<<< orphan*/  name; int /*<<< orphan*/ * internal_ops; struct media_entity entity; } ;
struct vpfe_ipipeif_device {TYPE_1__ video_in; int /*<<< orphan*/  ctrls; int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  ipipeif_base_addr; struct media_pad* pads; struct v4l2_subdev subdev; } ;
struct resource {int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct platform_device {int dummy; } ;
struct media_pad {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IPIPEIF_DEFAULT_GAIN ; 
 int /*<<< orphan*/  IPIPEIF_GAIN_HIGH ; 
 int /*<<< orphan*/  IPIPEIF_INPUT_NONE ; 
 int /*<<< orphan*/  IPIPEIF_NUM_PADS ; 
 int /*<<< orphan*/  IPIPEIF_OUTPUT_NONE ; 
 size_t IPIPEIF_PAD_SINK ; 
 size_t IPIPEIF_PAD_SOURCE ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipipeif_ctrl_ops ; 
 int /*<<< orphan*/  ipipeif_media_ops ; 
 int /*<<< orphan*/  ipipeif_set_default_config (struct vpfe_ipipeif_device*) ; 
 int /*<<< orphan*/  ipipeif_v4l2_internal_ops ; 
 int /*<<< orphan*/  ipipeif_v4l2_ops ; 
 int media_entity_pads_init (struct media_entity*,int /*<<< orphan*/ ,struct media_pad*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_custom (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct vpfe_ipipeif_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_in_ops ; 
 int /*<<< orphan*/  vpfe_ipipeif_dpcm_pred ; 
 int vpfe_video_init (TYPE_1__*,char*) ; 

int vpfe_ipipeif_init(struct vpfe_ipipeif_device *ipipeif,
		      struct platform_device *pdev)
{
	struct v4l2_subdev *sd = &ipipeif->subdev;
	struct media_pad *pads = &ipipeif->pads[0];
	struct media_entity *me = &sd->entity;
	static resource_size_t  res_len;
	struct resource *res;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 3);
	if (!res)
		return -ENOENT;

	res_len = resource_size(res);
	res = request_mem_region(res->start, res_len, res->name);
	if (!res)
		return -EBUSY;

	ipipeif->ipipeif_base_addr = ioremap_nocache(res->start, res_len);
	if (!ipipeif->ipipeif_base_addr) {
		ret =  -EBUSY;
		goto fail;
	}

	v4l2_subdev_init(sd, &ipipeif_v4l2_ops);

	sd->internal_ops = &ipipeif_v4l2_internal_ops;
	strlcpy(sd->name, "DAVINCI IPIPEIF", sizeof(sd->name));
	sd->grp_id = 1 << 16;	/* group ID for davinci subdevs */

	v4l2_set_subdevdata(sd, ipipeif);

	sd->flags |= V4L2_SUBDEV_FL_HAS_EVENTS | V4L2_SUBDEV_FL_HAS_DEVNODE;
	pads[IPIPEIF_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[IPIPEIF_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	ipipeif->input = IPIPEIF_INPUT_NONE;
	ipipeif->output = IPIPEIF_OUTPUT_NONE;
	me->ops = &ipipeif_media_ops;

	ret = media_entity_pads_init(me, IPIPEIF_NUM_PADS, pads);
	if (ret)
		goto fail;

	v4l2_ctrl_handler_init(&ipipeif->ctrls, 2);
	v4l2_ctrl_new_std(&ipipeif->ctrls, &ipipeif_ctrl_ops,
			  V4L2_CID_GAIN, 0,
			  IPIPEIF_GAIN_HIGH, 1, IPIPEIF_DEFAULT_GAIN);
	v4l2_ctrl_new_custom(&ipipeif->ctrls, &vpfe_ipipeif_dpcm_pred, NULL);
	v4l2_ctrl_handler_setup(&ipipeif->ctrls);
	sd->ctrl_handler = &ipipeif->ctrls;

	ipipeif->video_in.ops = &video_in_ops;
	ipipeif->video_in.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = vpfe_video_init(&ipipeif->video_in, "IPIPEIF");
	if (ret) {
		pr_err("Failed to init IPIPEIF video-in device\n");
		goto fail;
	}
	ipipeif_set_default_config(ipipeif);
	return 0;
fail:
	release_mem_region(res->start, res_len);
	return ret;
}