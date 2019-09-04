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
struct TYPE_6__ {struct v4l2_mbus_framefmt* formats; } ;
struct TYPE_5__ {struct v4l2_mbus_framefmt* formats; } ;
struct resizer_params {TYPE_4__* ext_mem_param; TYPE_3__* rsz_rsc_param; } ;
struct vpfe_resizer_device {TYPE_2__ resizer_b; TYPE_1__ resizer_a; struct resizer_params config; } ;
struct v4l2_mbus_framefmt {int height; int width; scalar_t__ code; } ;
struct TYPE_8__ {int c_offset; int flip_ofst_y; int flip_ofst_c; int rsz_sdr_oft_y; int rsz_sdr_oft_c; } ;
struct TYPE_7__ {scalar_t__ v_flip; scalar_t__ h_flip; } ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_YDYUYDYV8_1X16 ; 
 size_t RESIZER_PAD_SOURCE ; 
 int RSZ_A ; 

__attribute__((used)) static int
resizer_calculate_sdram_offsets(struct vpfe_resizer_device *resizer, int index)
{
	struct resizer_params *param = &resizer->config;
	struct v4l2_mbus_framefmt *outformat;
	int bytesperpixel = 2;
	int image_height;
	int image_width;
	int yuv_420 = 0;
	int offset = 0;

	if (index == RSZ_A)
		outformat = &resizer->resizer_a.formats[RESIZER_PAD_SOURCE];
	else
		outformat = &resizer->resizer_b.formats[RESIZER_PAD_SOURCE];

	image_height = outformat->height + 1;
	image_width = outformat->width + 1;
	param->ext_mem_param[index].c_offset = 0;
	param->ext_mem_param[index].flip_ofst_y = 0;
	param->ext_mem_param[index].flip_ofst_c = 0;
	if (outformat->code == MEDIA_BUS_FMT_YDYUYDYV8_1X16) {
		/* YUV 420 */
		yuv_420 = 1;
		bytesperpixel = 1;
	}

	if (param->rsz_rsc_param[index].h_flip)
		/* width * bytesperpixel - 1 */
		offset = (image_width * bytesperpixel) - 1;
	if (param->rsz_rsc_param[index].v_flip)
		offset += (image_height - 1) *
			param->ext_mem_param[index].rsz_sdr_oft_y;
	param->ext_mem_param[index].flip_ofst_y = offset;
	if (!yuv_420)
		return 0;
	offset = 0;
	/* half height for c-plane */
	if (param->rsz_rsc_param[index].h_flip)
		/* width * bytesperpixel - 1 */
		offset = image_width - 1;
	if (param->rsz_rsc_param[index].v_flip)
		offset += (((image_height >> 1) - 1) *
			   param->ext_mem_param[index].rsz_sdr_oft_c);
	param->ext_mem_param[index].flip_ofst_c = offset;
	param->ext_mem_param[index].c_offset =
		      param->ext_mem_param[index].rsz_sdr_oft_y * image_height;
	return 0;
}