#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vpfe_rsz_config_params {int /*<<< orphan*/  chroma_sample_even; int /*<<< orphan*/  out_chr_pos; int /*<<< orphan*/  yuv_c_max; int /*<<< orphan*/  yuv_c_min; int /*<<< orphan*/  yuv_y_max; int /*<<< orphan*/  yuv_y_min; int /*<<< orphan*/  hst; int /*<<< orphan*/  vst; } ;
struct TYPE_3__ {scalar_t__ input; struct v4l2_mbus_framefmt* formats; } ;
struct TYPE_4__ {int hsz; int vsz; int raw_flip; int y_c; int /*<<< orphan*/  rsz_seq_crv; int /*<<< orphan*/  out_chr_pos; int /*<<< orphan*/  yuv_c_max; int /*<<< orphan*/  yuv_c_min; int /*<<< orphan*/  yuv_y_max; int /*<<< orphan*/  yuv_y_min; void* source; void* src_img_fmt; int /*<<< orphan*/  hps; int /*<<< orphan*/  vps; } ;
struct resizer_params {TYPE_2__ rsz_common; struct vpfe_rsz_config_params user_config; } ;
struct vpfe_resizer_device {TYPE_1__ crop_resizer; struct resizer_params config; } ;
struct vpfe_device {int dummy; } ;
struct v4l2_mbus_framefmt {int width; scalar_t__ field; int height; int code; } ;

/* Variables and functions */
 void* IPIPEIF_DATA ; 
 int IPIPEIF_RSZ_CONST ; 
 void* IPIPE_DATA ; 
#define  MEDIA_BUS_FMT_SGRBG12_1X12 131 
#define  MEDIA_BUS_FMT_UV8_1X8 130 
#define  MEDIA_BUS_FMT_UYVY8_2X8 129 
#define  MEDIA_BUS_FMT_Y8_1X8 128 
 scalar_t__ RESIZER_CROP_INPUT_IPIPEIF ; 
 size_t RESIZER_CROP_PAD_SINK ; 
 void* RSZ_IMG_420 ; 
 void* RSZ_IMG_422 ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_resizer_device*) ; 
 scalar_t__ vpfe_ipipeif_decimation_enabled (struct vpfe_device*) ; 
 int vpfe_ipipeif_get_rsz (struct vpfe_device*) ; 

__attribute__((used)) static int
resizer_configure_common_in_params(struct vpfe_resizer_device *resizer)
{
	struct vpfe_device *vpfe_dev = to_vpfe_device(resizer);
	struct resizer_params *param = &resizer->config;
	struct vpfe_rsz_config_params *user_config;
	struct v4l2_mbus_framefmt *informat;

	informat = &resizer->crop_resizer.formats[RESIZER_CROP_PAD_SINK];
	user_config = &resizer->config.user_config;
	param->rsz_common.vps = param->user_config.vst;
	param->rsz_common.hps = param->user_config.hst;

	if (vpfe_ipipeif_decimation_enabled(vpfe_dev))
		param->rsz_common.hsz = ((informat->width - 1) *
			IPIPEIF_RSZ_CONST) / vpfe_ipipeif_get_rsz(vpfe_dev);
	else
		param->rsz_common.hsz = informat->width - 1;

	if (informat->field == V4L2_FIELD_INTERLACED)
		param->rsz_common.vsz  = (informat->height - 1) >> 1;
	else
		param->rsz_common.vsz  = informat->height - 1;

	param->rsz_common.raw_flip = 0;

	if (resizer->crop_resizer.input == RESIZER_CROP_INPUT_IPIPEIF)
		param->rsz_common.source = IPIPEIF_DATA;
	else
		param->rsz_common.source = IPIPE_DATA;

	switch (informat->code) {
	case MEDIA_BUS_FMT_UYVY8_2X8:
		param->rsz_common.src_img_fmt = RSZ_IMG_422;
		param->rsz_common.raw_flip = 0;
		break;

	case MEDIA_BUS_FMT_Y8_1X8:
		param->rsz_common.src_img_fmt = RSZ_IMG_420;
		/* Select y */
		param->rsz_common.y_c = 0;
		param->rsz_common.raw_flip = 0;
		break;

	case MEDIA_BUS_FMT_UV8_1X8:
		param->rsz_common.src_img_fmt = RSZ_IMG_420;
		/* Select y */
		param->rsz_common.y_c = 1;
		param->rsz_common.raw_flip = 0;
		break;

	case MEDIA_BUS_FMT_SGRBG12_1X12:
		param->rsz_common.raw_flip = 1;
		break;

	default:
		param->rsz_common.src_img_fmt = RSZ_IMG_422;
		param->rsz_common.source = IPIPE_DATA;
	}

	param->rsz_common.yuv_y_min = user_config->yuv_y_min;
	param->rsz_common.yuv_y_max = user_config->yuv_y_max;
	param->rsz_common.yuv_c_min = user_config->yuv_c_min;
	param->rsz_common.yuv_c_max = user_config->yuv_c_max;
	param->rsz_common.out_chr_pos = user_config->out_chr_pos;
	param->rsz_common.rsz_seq_crv = user_config->chroma_sample_even;

	return 0;
}