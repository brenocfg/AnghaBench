#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct vpfe_rsz_config_params {scalar_t__ bypass; scalar_t__ frame_div_mode_en; int /*<<< orphan*/  output2; int /*<<< orphan*/  output1; } ;
struct TYPE_16__ {scalar_t__ output; struct v4l2_mbus_framefmt* formats; } ;
struct TYPE_15__ {scalar_t__ output; struct v4l2_mbus_framefmt* formats; } ;
struct TYPE_11__ {TYPE_1__* v4l2_dev; } ;
struct TYPE_12__ {struct v4l2_mbus_framefmt* formats; TYPE_2__ subdev; } ;
struct TYPE_13__ {int raw_flip; scalar_t__ passthrough; } ;
struct resizer_params {TYPE_4__ rsz_common; TYPE_8__* rsz_rsc_param; void** rsz_en; struct vpfe_rsz_config_params user_config; TYPE_5__* ext_mem_param; } ;
struct vpfe_resizer_device {TYPE_7__ resizer_b; TYPE_6__ resizer_a; TYPE_3__ crop_resizer; struct resizer_params config; } ;
struct vpfe_device {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int height; int /*<<< orphan*/  width; } ;
struct device {int dummy; } ;
struct TYPE_17__ {int v_dif; int o_vsz; int /*<<< orphan*/  dscale_en; } ;
struct TYPE_14__ {int rsz_sdr_oft_y; int rsz_sdr_oft_c; } ;
struct TYPE_10__ {struct device* dev; } ;

/* Variables and functions */
 void* DISABLE ; 
 int EINVAL ; 
 void* ENABLE ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 scalar_t__ MEDIA_BUS_FMT_UV8_1X8 ; 
 scalar_t__ MEDIA_BUS_FMT_YDYUYDYV8_1X16 ; 
 size_t RESIZER_CROP_PAD_SINK ; 
 scalar_t__ RESIZER_OUTPUT_NONE ; 
 size_t RESIZER_PAD_SOURCE ; 
 size_t RSZ_A ; 
 size_t RSZ_B ; 
 int /*<<< orphan*/  configure_resizer_out_params (struct vpfe_resizer_device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int resizer_calculate_down_scale_f_div_param (struct device*,int /*<<< orphan*/ ,int,TYPE_8__*) ; 
 int resizer_calculate_normal_f_div_param (struct device*,int /*<<< orphan*/ ,int,TYPE_8__*) ; 
 int /*<<< orphan*/  resizer_calculate_resize_ratios (struct vpfe_resizer_device*,size_t) ; 
 int /*<<< orphan*/  resizer_calculate_sdram_offsets (struct vpfe_resizer_device*,size_t) ; 
 int /*<<< orphan*/  resizer_configure_common_in_params (struct vpfe_resizer_device*) ; 
 int /*<<< orphan*/  resizer_configure_passthru (struct vpfe_resizer_device*,int) ; 
 int /*<<< orphan*/  resizer_enable_422_420_conversion (struct resizer_params*,size_t,void*) ; 
 int resizer_validate_decimation (struct device*,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int resizer_validate_input_image_format (struct device*,scalar_t__,int /*<<< orphan*/ ,int,int*) ; 
 int resizer_validate_output_image_format (struct device*,struct v4l2_mbus_framefmt*,int*,int*) ; 
 struct vpfe_device* to_vpfe_device (struct vpfe_resizer_device*) ; 
 int vpfe_ipipeif_decimation_enabled (struct vpfe_device*) ; 
 int vpfe_ipipeif_get_rsz (struct vpfe_device*) ; 

__attribute__((used)) static int
resizer_configure_in_single_shot_mode(struct vpfe_resizer_device *resizer)
{
	struct vpfe_rsz_config_params *config = &resizer->config.user_config;
	struct device *dev = resizer->crop_resizer.subdev.v4l2_dev->dev;
	struct vpfe_device *vpfe_dev = to_vpfe_device(resizer);
	struct v4l2_mbus_framefmt *outformat1, *outformat2;
	struct resizer_params *param = &resizer->config;
	struct v4l2_mbus_framefmt *informat;
	int decimation;
	int line_len_c;
	int line_len;
	int rsz;
	int ret;

	informat = &resizer->crop_resizer.formats[RESIZER_CROP_PAD_SINK];
	outformat1 = &resizer->resizer_a.formats[RESIZER_PAD_SOURCE];
	outformat2 = &resizer->resizer_b.formats[RESIZER_PAD_SOURCE];

	decimation = vpfe_ipipeif_decimation_enabled(vpfe_dev);
	rsz = vpfe_ipipeif_get_rsz(vpfe_dev);
	if (decimation && param->user_config.frame_div_mode_en) {
		dev_err(dev,
		"dec_en & frame_div_mode_en cannot enabled simultaneously\n");
		return -EINVAL;
	}

	ret = resizer_validate_decimation(dev, decimation, rsz,
	      param->user_config.frame_div_mode_en, informat->width);
	if (ret)
		return -EINVAL;

	ret = resizer_validate_input_image_format(dev, informat->code,
		informat->width, informat->height, &line_len);
	if (ret)
		return -EINVAL;

	if (resizer->resizer_a.output != RESIZER_OUTPUT_NONE) {
		param->rsz_en[RSZ_A] = ENABLE;
		ret = resizer_validate_output_image_format(dev, outformat1,
					&line_len, &line_len_c);
		if (ret)
			return ret;
		param->ext_mem_param[RSZ_A].rsz_sdr_oft_y = line_len;
		param->ext_mem_param[RSZ_A].rsz_sdr_oft_c = line_len_c;
		configure_resizer_out_params(resizer, RSZ_A,
					&param->user_config.output1, 0, 1);

		if (outformat1->code == MEDIA_BUS_FMT_SGRBG12_1X12)
			param->rsz_common.raw_flip = 1;
		else
			param->rsz_common.raw_flip = 0;

		if (outformat1->code == MEDIA_BUS_FMT_YDYUYDYV8_1X16)
			resizer_enable_422_420_conversion(param,
							  RSZ_A, ENABLE);
		else
			resizer_enable_422_420_conversion(param,
							  RSZ_A, DISABLE);
	}

	if (resizer->resizer_b.output != RESIZER_OUTPUT_NONE) {
		param->rsz_en[RSZ_B] = ENABLE;
		ret = resizer_validate_output_image_format(dev, outformat2,
				&line_len, &line_len_c);
		if (ret)
			return ret;
		param->ext_mem_param[RSZ_B].rsz_sdr_oft_y = line_len;
		param->ext_mem_param[RSZ_B].rsz_sdr_oft_c = line_len_c;
		configure_resizer_out_params(resizer, RSZ_B,
					&param->user_config.output2, 0, 1);
		if (outformat2->code == MEDIA_BUS_FMT_YDYUYDYV8_1X16)
			resizer_enable_422_420_conversion(param,
							  RSZ_B, ENABLE);
		else
			resizer_enable_422_420_conversion(param,
							  RSZ_B, DISABLE);
	}

	resizer_configure_common_in_params(resizer);
	if (resizer->resizer_a.output != RESIZER_OUTPUT_NONE) {
		resizer_calculate_resize_ratios(resizer, RSZ_A);
		resizer_calculate_sdram_offsets(resizer, RSZ_A);
		/* Overriding resize ratio calculation */
		if (informat->code == MEDIA_BUS_FMT_UV8_1X8) {
			param->rsz_rsc_param[RSZ_A].v_dif =
				(((informat->height + 1) * 2) * 256) /
				(param->rsz_rsc_param[RSZ_A].o_vsz + 1);
		}
	}

	if (resizer->resizer_b.output != RESIZER_OUTPUT_NONE) {
		resizer_calculate_resize_ratios(resizer, RSZ_B);
		resizer_calculate_sdram_offsets(resizer, RSZ_B);
		/* Overriding resize ratio calculation */
		if (informat->code == MEDIA_BUS_FMT_UV8_1X8) {
			param->rsz_rsc_param[RSZ_B].v_dif =
				(((informat->height + 1) * 2) * 256) /
				(param->rsz_rsc_param[RSZ_B].o_vsz + 1);
		}
	}
	if (param->user_config.frame_div_mode_en &&
		param->rsz_en[RSZ_A]) {
		if (!param->rsz_rsc_param[RSZ_A].dscale_en)
			ret = resizer_calculate_normal_f_div_param(dev,
			      informat->width,
			      param->rsz_rsc_param[RSZ_A].o_vsz + 1,
			      &param->rsz_rsc_param[RSZ_A]);
		else
			ret = resizer_calculate_down_scale_f_div_param(dev,
			      informat->width,
			      param->rsz_rsc_param[RSZ_A].o_vsz + 1,
			      &param->rsz_rsc_param[RSZ_A]);
		if (ret)
			return -EINVAL;
	}
	if (param->user_config.frame_div_mode_en &&
		param->rsz_en[RSZ_B]) {
		if (!param->rsz_rsc_param[RSZ_B].dscale_en)
			ret = resizer_calculate_normal_f_div_param(dev,
			      informat->width,
			      param->rsz_rsc_param[RSZ_B].o_vsz + 1,
			      &param->rsz_rsc_param[RSZ_B]);
		else
			ret = resizer_calculate_down_scale_f_div_param(dev,
			      informat->width,
			      param->rsz_rsc_param[RSZ_B].o_vsz + 1,
			      &param->rsz_rsc_param[RSZ_B]);
		if (ret)
			return -EINVAL;
	}
	param->rsz_common.passthrough = config->bypass;
	if (config->bypass)
		resizer_configure_passthru(resizer, 1);
	return 0;
}