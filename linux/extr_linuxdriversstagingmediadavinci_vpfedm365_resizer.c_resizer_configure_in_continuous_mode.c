#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vpfe_rsz_config_params {scalar_t__ bypass; int /*<<< orphan*/  output2; int /*<<< orphan*/  output1; } ;
struct TYPE_12__ {scalar_t__ output; struct v4l2_mbus_framefmt* formats; } ;
struct TYPE_14__ {scalar_t__ passthrough; } ;
struct resizer_params {TYPE_7__ rsz_common; TYPE_6__* ext_mem_param; void** rsz_en; int /*<<< orphan*/  oper_mode; struct vpfe_rsz_config_params user_config; } ;
struct TYPE_11__ {scalar_t__ output; } ;
struct TYPE_9__ {TYPE_1__* v4l2_dev; } ;
struct TYPE_10__ {TYPE_2__ subdev; } ;
struct vpfe_resizer_device {TYPE_5__ resizer_b; struct resizer_params config; TYPE_4__ resizer_a; TYPE_3__ crop_resizer; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; } ;
struct device {int dummy; } ;
struct TYPE_13__ {int rsz_sdr_oft_y; int rsz_sdr_oft_c; } ;
struct TYPE_8__ {struct device* dev; } ;

/* Variables and functions */
 void* DISABLE ; 
 int EINVAL ; 
 void* ENABLE ; 
 scalar_t__ MEDIA_BUS_FMT_YDYUYDYV8_1X16 ; 
 int /*<<< orphan*/  RESIZER_MODE_CONTINIOUS ; 
 scalar_t__ RESIZER_OUTPUT_MEMORY ; 
 size_t RESIZER_PAD_SOURCE ; 
 size_t RSZ_A ; 
 size_t RSZ_B ; 
 int /*<<< orphan*/  configure_resizer_out_params (struct vpfe_resizer_device*,size_t,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  resizer_configure_common_in_params (struct vpfe_resizer_device*) ; 
 int resizer_configure_output_win (struct vpfe_resizer_device*) ; 
 int /*<<< orphan*/  resizer_configure_passthru (struct vpfe_resizer_device*,int) ; 
 int /*<<< orphan*/  resizer_enable_422_420_conversion (struct resizer_params*,size_t,void*) ; 
 int resizer_validate_output_image_format (struct device*,struct v4l2_mbus_framefmt*,int*,int*) ; 

__attribute__((used)) static int
resizer_configure_in_continuous_mode(struct vpfe_resizer_device *resizer)
{
	struct device *dev = resizer->crop_resizer.subdev.v4l2_dev->dev;
	struct resizer_params *param = &resizer->config;
	struct vpfe_rsz_config_params *cont_config;
	int line_len_c;
	int line_len;
	int ret;

	if (resizer->resizer_a.output != RESIZER_OUTPUT_MEMORY) {
		dev_err(dev, "enable resizer - Resizer-A\n");
		return -EINVAL;
	}

	cont_config = &resizer->config.user_config;
	param->rsz_en[RSZ_A] = ENABLE;
	configure_resizer_out_params(resizer, RSZ_A,
				     &cont_config->output1, 1, 0);
	param->rsz_en[RSZ_B] = DISABLE;
	param->oper_mode = RESIZER_MODE_CONTINIOUS;

	if (resizer->resizer_b.output == RESIZER_OUTPUT_MEMORY) {
		struct v4l2_mbus_framefmt *outformat2;

		param->rsz_en[RSZ_B] = ENABLE;
		outformat2 = &resizer->resizer_b.formats[RESIZER_PAD_SOURCE];
		ret = resizer_validate_output_image_format(dev, outformat2,
				&line_len, &line_len_c);
		if (ret)
			return ret;
		param->ext_mem_param[RSZ_B].rsz_sdr_oft_y = line_len;
		param->ext_mem_param[RSZ_B].rsz_sdr_oft_c = line_len_c;
		configure_resizer_out_params(resizer, RSZ_B,
						&cont_config->output2, 0, 1);
		if (outformat2->code == MEDIA_BUS_FMT_YDYUYDYV8_1X16)
			resizer_enable_422_420_conversion(param,
							  RSZ_B, ENABLE);
		else
			resizer_enable_422_420_conversion(param,
							  RSZ_B, DISABLE);
	}
	resizer_configure_common_in_params(resizer);
	ret = resizer_configure_output_win(resizer);
	if (ret)
		return ret;

	param->rsz_common.passthrough = cont_config->bypass;
	if (cont_config->bypass)
		resizer_configure_passthru(resizer, 1);

	return 0;
}