#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct TYPE_6__ {TYPE_2__ video; } ;
struct TYPE_4__ {int /*<<< orphan*/  entity; } ;
struct iss_ipipeif_device {TYPE_3__ video_out; TYPE_1__ subdev; } ;
struct iss_device {struct iss_ipipeif_device ipipeif; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPIPEIF_PAD_SOURCE_ISIF_SF ; 
 int media_create_pad_link (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omap4iss_ipipeif_create_links(struct iss_device *iss)
{
	struct iss_ipipeif_device *ipipeif = &iss->ipipeif;

	/* Connect the IPIPEIF subdev to the video node. */
	return media_create_pad_link(&ipipeif->subdev.entity,
				     IPIPEIF_PAD_SOURCE_ISIF_SF,
				     &ipipeif->video_out.video.entity, 0, 0);
}