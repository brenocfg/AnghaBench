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
struct TYPE_7__ {struct v4l2_mbus_framefmt* formats; } ;
struct TYPE_6__ {struct v4l2_mbus_framefmt* formats; } ;
struct TYPE_5__ {struct v4l2_mbus_framefmt* formats; } ;
struct resizer_params {TYPE_4__* rsz_rsc_param; } ;
struct vpfe_resizer_device {TYPE_3__ resizer_b; TYPE_2__ resizer_a; TYPE_1__ crop_resizer; struct resizer_params config; } ;
struct v4l2_mbus_framefmt {scalar_t__ field; int height; int width; } ;
struct TYPE_8__ {int v_dif; int h_dif; } ;

/* Variables and functions */
 size_t RESIZER_CROP_PAD_SINK ; 
 size_t RESIZER_PAD_SOURCE ; 
 int RSZ_A ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 

__attribute__((used)) static void
resizer_calculate_resize_ratios(struct vpfe_resizer_device *resizer, int index)
{
	struct resizer_params *param = &resizer->config;
	struct v4l2_mbus_framefmt *informat, *outformat;

	informat = &resizer->crop_resizer.formats[RESIZER_CROP_PAD_SINK];

	if (index == RSZ_A)
		outformat = &resizer->resizer_a.formats[RESIZER_PAD_SOURCE];
	else
		outformat = &resizer->resizer_b.formats[RESIZER_PAD_SOURCE];

	if (outformat->field != V4L2_FIELD_INTERLACED)
		param->rsz_rsc_param[index].v_dif =
			((informat->height) * 256) / (outformat->height);
	else
		param->rsz_rsc_param[index].v_dif =
			((informat->height >> 1) * 256) / (outformat->height);
	param->rsz_rsc_param[index].h_dif =
			((informat->width) * 256) / (outformat->width);
}