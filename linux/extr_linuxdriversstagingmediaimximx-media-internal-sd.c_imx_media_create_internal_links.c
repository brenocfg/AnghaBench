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
struct TYPE_2__ {int num_pads; struct media_pad* pads; } ;
struct v4l2_subdev {TYPE_1__ entity; int /*<<< orphan*/  grp_id; } ;
struct media_pad {int flags; } ;
struct internal_subdev {struct internal_pad* pad; } ;
struct internal_pad {struct internal_link* link; } ;
struct internal_link {int /*<<< orphan*/  remote; } ;
struct imx_media_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int MEDIA_PAD_FL_SOURCE ; 
 int create_ipu_internal_link (struct imx_media_dev*,struct v4l2_subdev*,struct internal_link const*) ; 
 struct internal_subdev* find_intsd_by_grp_id (int /*<<< orphan*/ ) ; 

int imx_media_create_internal_links(struct imx_media_dev *imxmd,
				    struct v4l2_subdev *sd)
{
	const struct internal_subdev *intsd;
	const struct internal_pad *intpad;
	const struct internal_link *link;
	struct media_pad *pad;
	int i, j, ret;

	intsd = find_intsd_by_grp_id(sd->grp_id);
	if (!intsd)
		return -ENODEV;

	/* create the source->sink links */
	for (i = 0; i < sd->entity.num_pads; i++) {
		intpad = &intsd->pad[i];
		pad = &sd->entity.pads[i];

		if (!(pad->flags & MEDIA_PAD_FL_SOURCE))
			continue;

		for (j = 0; ; j++) {
			link = &intpad->link[j];

			if (!link->remote)
				break;

			ret = create_ipu_internal_link(imxmd, sd, link);
			if (ret)
				return ret;
		}
	}

	return 0;
}