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
struct media_entity {int /*<<< orphan*/ * ops; } ;
struct v4l2_subdev {int grp_id; int /*<<< orphan*/ * ctrl_handler; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * internal_ops; struct media_entity entity; } ;
struct vpfe_ipipe_device {void* base_addr; int /*<<< orphan*/  ctrls; int /*<<< orphan*/  output; int /*<<< orphan*/  input; void* isp5_base_addr; struct v4l2_subdev subdev; struct media_pad* pads; } ;
struct resource {int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct platform_device {int dummy; } ;
struct media_pad {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IPIPE_BRIGHT_HIGH ; 
 int /*<<< orphan*/  IPIPE_CONTRAST_HIGH ; 
 int /*<<< orphan*/  IPIPE_INPUT_NONE ; 
 int /*<<< orphan*/  IPIPE_OUTPUT_NONE ; 
 int /*<<< orphan*/  IPIPE_PADS_NUM ; 
 size_t IPIPE_PAD_SINK ; 
 size_t IPIPE_PAD_SOURCE ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 void* ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  ipipe_ctrl_ops ; 
 int /*<<< orphan*/  ipipe_media_ops ; 
 int /*<<< orphan*/  ipipe_v4l2_internal_ops ; 
 int /*<<< orphan*/  ipipe_v4l2_ops ; 
 int media_entity_pads_init (struct media_entity*,int /*<<< orphan*/ ,struct media_pad*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct vpfe_ipipe_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

int
vpfe_ipipe_init(struct vpfe_ipipe_device *ipipe, struct platform_device *pdev)
{
	struct media_pad *pads = &ipipe->pads[0];
	struct v4l2_subdev *sd = &ipipe->subdev;
	struct media_entity *me = &sd->entity;
	struct resource *res, *memres;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 4);
	if (!res)
		return -ENOENT;

	memres = request_mem_region(res->start, resource_size(res), res->name);
	if (!memres)
		return -EBUSY;
	ipipe->base_addr = ioremap_nocache(memres->start,
					   resource_size(memres));
	if (!ipipe->base_addr)
		goto error_release;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 6);
	if (!res)
		goto error_unmap;
	ipipe->isp5_base_addr = ioremap_nocache(res->start,
						resource_size(res));
	if (!ipipe->isp5_base_addr)
		goto error_unmap;

	v4l2_subdev_init(sd, &ipipe_v4l2_ops);
	sd->internal_ops = &ipipe_v4l2_internal_ops;
	strlcpy(sd->name, "DAVINCI IPIPE", sizeof(sd->name));
	sd->grp_id = 1 << 16;	/* group ID for davinci subdevs */
	v4l2_set_subdevdata(sd, ipipe);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[IPIPE_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[IPIPE_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	ipipe->input = IPIPE_INPUT_NONE;
	ipipe->output = IPIPE_OUTPUT_NONE;

	me->ops = &ipipe_media_ops;
	v4l2_ctrl_handler_init(&ipipe->ctrls, 2);
	v4l2_ctrl_new_std(&ipipe->ctrls, &ipipe_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, 0,
			  IPIPE_BRIGHT_HIGH, 1, 16);
	v4l2_ctrl_new_std(&ipipe->ctrls, &ipipe_ctrl_ops,
			  V4L2_CID_CONTRAST, 0,
			  IPIPE_CONTRAST_HIGH, 1, 16);


	v4l2_ctrl_handler_setup(&ipipe->ctrls);
	sd->ctrl_handler = &ipipe->ctrls;

	return media_entity_pads_init(me, IPIPE_PADS_NUM, pads);

error_unmap:
	iounmap(ipipe->base_addr);
error_release:
	release_mem_region(memres->start, resource_size(memres));
	return -ENOMEM;
}