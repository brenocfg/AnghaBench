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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct internal_link {int /*<<< orphan*/  remote; } ;
struct imx_media_dev {int dummy; } ;
typedef  int /*<<< orphan*/  sink_devname ;

/* Variables and functions */
 struct v4l2_subdev* imx_media_find_subdev_by_devname (struct imx_media_dev*,char*) ; 
 int /*<<< orphan*/  isd_to_devname (char*,int,int /*<<< orphan*/ ,int) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static struct v4l2_subdev *find_sink(struct imx_media_dev *imxmd,
				     struct v4l2_subdev *src,
				     const struct internal_link *link)
{
	char sink_devname[32];
	int ipu_id;

	/*
	 * retrieve IPU id from subdev name, note: can't get this from
	 * struct imx_media_internal_sd_platformdata because if src is
	 * a CSI, it has different struct ipu_client_platformdata which
	 * does not contain IPU id.
	 */
	if (sscanf(src->name, "ipu%d", &ipu_id) != 1)
		return NULL;

	isd_to_devname(sink_devname, sizeof(sink_devname),
		       link->remote, ipu_id - 1);

	return imx_media_find_subdev_by_devname(imxmd, sink_devname);
}