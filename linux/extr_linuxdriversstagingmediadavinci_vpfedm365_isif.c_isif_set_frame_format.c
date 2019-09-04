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
struct TYPE_7__ {int frm_fmt; } ;
struct TYPE_6__ {int frm_fmt; } ;
struct TYPE_8__ {TYPE_3__ ycbcr; TYPE_2__ bayer; } ;
struct vpfe_isif_device {TYPE_4__ isif_cfg; TYPE_1__* formats; } ;
typedef  enum isif_frmfmt { ____Placeholder_isif_frmfmt } isif_frmfmt ;
struct TYPE_5__ {scalar_t__ code; } ;

/* Variables and functions */
 size_t ISIF_PAD_SINK ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 

__attribute__((used)) static int
isif_set_frame_format(struct vpfe_isif_device *isif,
		      enum isif_frmfmt frm_fmt)
{
	if (isif->formats[ISIF_PAD_SINK].code == MEDIA_BUS_FMT_SGRBG12_1X12)
		isif->isif_cfg.bayer.frm_fmt = frm_fmt;
	else
		isif->isif_cfg.ycbcr.frm_fmt = frm_fmt;

	return 0;
}