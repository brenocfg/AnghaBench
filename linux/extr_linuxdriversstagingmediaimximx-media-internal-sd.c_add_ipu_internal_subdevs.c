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
struct internal_subdev {TYPE_1__* id; } ;
struct imx_media_dev {int dummy; } ;
typedef  enum isd_enum { ____Placeholder_isd_enum } isd_enum ;
struct TYPE_2__ {int grp_id; } ;

/* Variables and functions */
#define  IMX_MEDIA_GRP_ID_CSI0 129 
#define  IMX_MEDIA_GRP_ID_CSI1 128 
 int add_internal_subdev (struct imx_media_dev*,struct internal_subdev const*,int) ; 
 struct internal_subdev* int_subdev ; 
 int num_isd ; 

__attribute__((used)) static int add_ipu_internal_subdevs(struct imx_media_dev *imxmd, int ipu_id)
{
	enum isd_enum i;

	for (i = 0; i < num_isd; i++) {
		const struct internal_subdev *isd = &int_subdev[i];
		int ret;

		/*
		 * the CSIs are represented in the device-tree, so those
		 * devices are already added to the async subdev list by
		 * of_parse_subdev().
		 */
		switch (isd->id->grp_id) {
		case IMX_MEDIA_GRP_ID_CSI0:
		case IMX_MEDIA_GRP_ID_CSI1:
			ret = 0;
			break;
		default:
			ret = add_internal_subdev(imxmd, isd, ipu_id);
			break;
		}

		if (ret)
			return ret;
	}

	return 0;
}