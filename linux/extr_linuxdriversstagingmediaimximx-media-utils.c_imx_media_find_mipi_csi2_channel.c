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
struct media_pad {int index; } ;
struct media_entity {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct imx_media_dev {TYPE_1__ md; } ;

/* Variables and functions */
 int EPIPE ; 
 int /*<<< orphan*/  IMX_MEDIA_GRP_ID_CSI2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 struct media_pad* find_pipeline_pad (struct imx_media_dev*,struct media_entity*,int /*<<< orphan*/ ,int) ; 

int imx_media_find_mipi_csi2_channel(struct imx_media_dev *imxmd,
				     struct media_entity *start_entity)
{
	struct media_pad *pad;
	int ret = -EPIPE;

	pad = find_pipeline_pad(imxmd, start_entity, IMX_MEDIA_GRP_ID_CSI2,
				true);
	if (pad) {
		ret = pad->index - 1;
		dev_dbg(imxmd->md.dev, "found vc%d from %s\n",
			ret, start_entity->name);
	}

	return ret;
}