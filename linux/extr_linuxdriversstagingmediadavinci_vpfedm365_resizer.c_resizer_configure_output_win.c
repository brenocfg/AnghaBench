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
struct vpfe_rsz_output_spec {int /*<<< orphan*/  vst_c; int /*<<< orphan*/  vst_y; } ;
struct TYPE_5__ {struct v4l2_mbus_framefmt* formats; } ;
struct TYPE_6__ {int /*<<< orphan*/  vst; } ;
struct resizer_params {scalar_t__* rsz_en; TYPE_4__* ext_mem_param; TYPE_3__* rsz_rsc_param; TYPE_2__ user_config; } ;
struct vpfe_resizer_device {TYPE_1__ resizer_a; struct resizer_params config; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; } ;
struct TYPE_8__ {int rsz_sdr_oft_y; int rsz_sdr_oft_c; } ;
struct TYPE_7__ {scalar_t__ o_vsz; scalar_t__ o_hsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE ; 
 int /*<<< orphan*/  ENABLE ; 
 scalar_t__ MEDIA_BUS_FMT_YDYUYDYV8_1X16 ; 
 size_t RESIZER_PAD_SOURCE ; 
 size_t RSZ_A ; 
 size_t RSZ_B ; 
 int /*<<< orphan*/  configure_resizer_out_params (struct vpfe_resizer_device*,size_t,struct vpfe_rsz_output_spec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct vpfe_rsz_output_spec*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  resizer_calculate_line_length (scalar_t__,scalar_t__,scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  resizer_calculate_resize_ratios (struct vpfe_resizer_device*,size_t) ; 
 int resizer_calculate_sdram_offsets (struct vpfe_resizer_device*,size_t) ; 
 int /*<<< orphan*/  resizer_enable_422_420_conversion (struct resizer_params*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resizer_configure_output_win(struct vpfe_resizer_device *resizer)
{
	struct resizer_params *param = &resizer->config;
	struct vpfe_rsz_output_spec output_specs;
	struct v4l2_mbus_framefmt *outformat;
	int line_len_c;
	int line_len;
	int ret;

	outformat = &resizer->resizer_a.formats[RESIZER_PAD_SOURCE];

	memset(&output_specs, 0x0, sizeof(struct vpfe_rsz_output_spec));
	output_specs.vst_y = param->user_config.vst;
	if (outformat->code == MEDIA_BUS_FMT_YDYUYDYV8_1X16)
		output_specs.vst_c = param->user_config.vst;

	configure_resizer_out_params(resizer, RSZ_A, &output_specs, 0, 0);
	resizer_calculate_line_length(outformat->code,
				      param->rsz_rsc_param[0].o_hsz + 1,
				      param->rsz_rsc_param[0].o_vsz + 1,
				      &line_len, &line_len_c);
	param->ext_mem_param[0].rsz_sdr_oft_y = line_len;
	param->ext_mem_param[0].rsz_sdr_oft_c = line_len_c;
	resizer_calculate_resize_ratios(resizer, RSZ_A);
	if (param->rsz_en[RSZ_B])
		resizer_calculate_resize_ratios(resizer, RSZ_B);

	if (outformat->code == MEDIA_BUS_FMT_YDYUYDYV8_1X16)
		resizer_enable_422_420_conversion(param, RSZ_A, ENABLE);
	else
		resizer_enable_422_420_conversion(param, RSZ_A, DISABLE);

	ret = resizer_calculate_sdram_offsets(resizer, RSZ_A);
	if (!ret && param->rsz_en[RSZ_B])
		ret = resizer_calculate_sdram_offsets(resizer, RSZ_B);

	if (ret)
		pr_err("Error in calculating sdram offsets\n");
	return ret;
}