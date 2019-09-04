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
struct v4l2_subdev {int /*<<< orphan*/  entity; int /*<<< orphan*/  name; } ;
struct internal_link {int /*<<< orphan*/  remote_pad; int /*<<< orphan*/  local_pad; } ;
struct imx_media_dev {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 struct v4l2_subdev* find_sink (struct imx_media_dev*,struct v4l2_subdev*,struct internal_link const*) ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_ipu_internal_link(struct imx_media_dev *imxmd,
				    struct v4l2_subdev *src,
				    const struct internal_link *link)
{
	struct v4l2_subdev *sink;
	int ret;

	sink = find_sink(imxmd, src, link);
	if (!sink)
		return -ENODEV;

	v4l2_info(&imxmd->v4l2_dev, "%s:%d -> %s:%d\n",
		  src->name, link->local_pad,
		  sink->name, link->remote_pad);

	ret = media_create_pad_link(&src->entity, link->local_pad,
				    &sink->entity, link->remote_pad, 0);
	if (ret)
		v4l2_err(&imxmd->v4l2_dev,
			 "create_pad_link failed: %d\n", ret);

	return ret;
}