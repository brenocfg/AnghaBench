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
struct TYPE_8__ {void* type; int /*<<< orphan*/ * ops; } ;
struct media_entity {int /*<<< orphan*/ * ops; } ;
struct v4l2_subdev {int grp_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/ * internal_ops; struct media_entity entity; } ;
struct TYPE_7__ {TYPE_4__ video_out; struct vpfe_resizer_device* rsz_device; void* output; void* input; struct media_pad* pads; struct v4l2_subdev subdev; } ;
struct TYPE_6__ {TYPE_4__ video_out; struct vpfe_resizer_device* rsz_device; void* output; void* input; struct media_pad* pads; struct v4l2_subdev subdev; } ;
struct TYPE_5__ {struct vpfe_resizer_device* rsz_device; void* output2; void* output; int /*<<< orphan*/  input; struct media_pad* pads; struct v4l2_subdev subdev; } ;
struct vpfe_resizer_device {int /*<<< orphan*/  config; TYPE_3__ resizer_b; TYPE_2__ resizer_a; TYPE_1__ crop_resizer; int /*<<< orphan*/  base_addr; } ;
struct resource {int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct resizer_params {int dummy; } ;
struct platform_device {int dummy; } ;
struct media_pad {void* flags; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 void* MEDIA_PAD_FL_SINK ; 
 void* MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  RESIZER_CROP_INPUT_NONE ; 
 void* RESIZER_CROP_OUTPUT_NONE ; 
 int /*<<< orphan*/  RESIZER_CROP_PADS_NUM ; 
 size_t RESIZER_CROP_PAD_SINK ; 
 size_t RESIZER_CROP_PAD_SOURCE ; 
 size_t RESIZER_CROP_PAD_SOURCE2 ; 
 void* RESIZER_INPUT_NONE ; 
 void* RESIZER_OUTPUT_NONE ; 
 int /*<<< orphan*/  RESIZER_PADS_NUM ; 
 size_t RESIZER_PAD_SINK ; 
 size_t RESIZER_PAD_SOURCE ; 
 void* V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int media_entity_pads_init (struct media_entity*,int /*<<< orphan*/ ,struct media_pad*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct resource* request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resizer_a_video_ops ; 
 int /*<<< orphan*/  resizer_b_video_ops ; 
 int /*<<< orphan*/  resizer_media_ops ; 
 int /*<<< orphan*/  resizer_v4l2_internal_ops ; 
 int /*<<< orphan*/  resizer_v4l2_ops ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct vpfe_resizer_device*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int vpfe_video_init (TYPE_4__*,char*) ; 

int vpfe_resizer_init(struct vpfe_resizer_device *vpfe_rsz,
		      struct platform_device *pdev)
{
	struct v4l2_subdev *sd = &vpfe_rsz->crop_resizer.subdev;
	struct media_pad *pads = &vpfe_rsz->crop_resizer.pads[0];
	struct media_entity *me = &sd->entity;
	static resource_size_t  res_len;
	struct resource *res;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 5);
	if (!res)
		return -ENOENT;

	res_len = resource_size(res);
	res = request_mem_region(res->start, res_len, res->name);
	if (!res)
		return -EBUSY;

	vpfe_rsz->base_addr = ioremap_nocache(res->start, res_len);
	if (!vpfe_rsz->base_addr)
		return -EBUSY;

	v4l2_subdev_init(sd, &resizer_v4l2_ops);
	sd->internal_ops = &resizer_v4l2_internal_ops;
	strlcpy(sd->name, "DAVINCI RESIZER CROP", sizeof(sd->name));
	sd->grp_id = 1 << 16;	/* group ID for davinci subdevs */
	v4l2_set_subdevdata(sd, vpfe_rsz);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[RESIZER_CROP_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[RESIZER_CROP_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;
	pads[RESIZER_CROP_PAD_SOURCE2].flags = MEDIA_PAD_FL_SOURCE;

	vpfe_rsz->crop_resizer.input = RESIZER_CROP_INPUT_NONE;
	vpfe_rsz->crop_resizer.output = RESIZER_CROP_OUTPUT_NONE;
	vpfe_rsz->crop_resizer.output2 = RESIZER_CROP_OUTPUT_NONE;
	vpfe_rsz->crop_resizer.rsz_device = vpfe_rsz;
	me->ops = &resizer_media_ops;
	ret = media_entity_pads_init(me, RESIZER_CROP_PADS_NUM, pads);
	if (ret)
		return ret;

	sd = &vpfe_rsz->resizer_a.subdev;
	pads = &vpfe_rsz->resizer_a.pads[0];
	me = &sd->entity;

	v4l2_subdev_init(sd, &resizer_v4l2_ops);
	sd->internal_ops = &resizer_v4l2_internal_ops;
	strlcpy(sd->name, "DAVINCI RESIZER A", sizeof(sd->name));
	sd->grp_id = 1 << 16;	/* group ID for davinci subdevs */
	v4l2_set_subdevdata(sd, vpfe_rsz);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[RESIZER_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[RESIZER_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	vpfe_rsz->resizer_a.input = RESIZER_INPUT_NONE;
	vpfe_rsz->resizer_a.output = RESIZER_OUTPUT_NONE;
	vpfe_rsz->resizer_a.rsz_device = vpfe_rsz;
	me->ops = &resizer_media_ops;
	ret = media_entity_pads_init(me, RESIZER_PADS_NUM, pads);
	if (ret)
		return ret;

	sd = &vpfe_rsz->resizer_b.subdev;
	pads = &vpfe_rsz->resizer_b.pads[0];
	me = &sd->entity;

	v4l2_subdev_init(sd, &resizer_v4l2_ops);
	sd->internal_ops = &resizer_v4l2_internal_ops;
	strlcpy(sd->name, "DAVINCI RESIZER B", sizeof(sd->name));
	sd->grp_id = 1 << 16;	/* group ID for davinci subdevs */
	v4l2_set_subdevdata(sd, vpfe_rsz);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	pads[RESIZER_PAD_SINK].flags = MEDIA_PAD_FL_SINK;
	pads[RESIZER_PAD_SOURCE].flags = MEDIA_PAD_FL_SOURCE;

	vpfe_rsz->resizer_b.input = RESIZER_INPUT_NONE;
	vpfe_rsz->resizer_b.output = RESIZER_OUTPUT_NONE;
	vpfe_rsz->resizer_b.rsz_device = vpfe_rsz;
	me->ops = &resizer_media_ops;
	ret = media_entity_pads_init(me, RESIZER_PADS_NUM, pads);
	if (ret)
		return ret;

	vpfe_rsz->resizer_a.video_out.ops = &resizer_a_video_ops;
	vpfe_rsz->resizer_a.video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = vpfe_video_init(&vpfe_rsz->resizer_a.video_out, "RSZ-A");
	if (ret) {
		pr_err("Failed to init RSZ video-out device\n");
		return ret;
	}
	vpfe_rsz->resizer_b.video_out.ops = &resizer_b_video_ops;
	vpfe_rsz->resizer_b.video_out.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = vpfe_video_init(&vpfe_rsz->resizer_b.video_out, "RSZ-B");
	if (ret) {
		pr_err("Failed to init RSZ video-out2 device\n");
		return ret;
	}
	memset(&vpfe_rsz->config, 0, sizeof(struct resizer_params));

	return 0;
}