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
struct vpfe_rsz_output_spec {int user_y_ofst; int user_c_ofst; int /*<<< orphan*/  h_dscale_ave_sz; int /*<<< orphan*/  en_down_scale; int /*<<< orphan*/  h_lpf_int_c; int /*<<< orphan*/  h_lpf_int_y; int /*<<< orphan*/  h_typ_c; int /*<<< orphan*/  h_typ_y; int /*<<< orphan*/  v_lpf_int_c; int /*<<< orphan*/  v_lpf_int_y; int /*<<< orphan*/  v_typ_c; int /*<<< orphan*/  v_typ_y; int /*<<< orphan*/  v_flip; int /*<<< orphan*/  h_flip; int /*<<< orphan*/  vst_c; int /*<<< orphan*/  vst_y; int /*<<< orphan*/  v_dscale_ave_sz; } ;
struct TYPE_6__ {scalar_t__ output; struct v4l2_mbus_framefmt* formats; } ;
struct TYPE_5__ {scalar_t__ output; struct v4l2_mbus_framefmt* formats; } ;
struct resizer_params {TYPE_4__* ext_mem_param; TYPE_3__* rsz_rsc_param; void** rsz_en; } ;
struct vpfe_resizer_device {TYPE_2__ resizer_b; TYPE_1__ resizer_a; struct resizer_params config; } ;
struct v4l2_mbus_framefmt {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_8__ {int user_y_ofst; int user_c_ofst; scalar_t__ rsz_sdr_ptr_e_c; int /*<<< orphan*/  rsz_sdr_ptr_s_c; scalar_t__ rsz_sdr_ptr_e_y; int /*<<< orphan*/  rsz_sdr_ptr_s_y; } ;
struct TYPE_7__ {int /*<<< orphan*/  v_dscale_ave_sz; int /*<<< orphan*/  h_dscale_ave_sz; int /*<<< orphan*/  dscale_en; int /*<<< orphan*/  h_lpf_int_c; int /*<<< orphan*/  h_lpf_int_y; int /*<<< orphan*/  h_typ_c; int /*<<< orphan*/  h_typ_y; int /*<<< orphan*/  v_lpf_int_c; int /*<<< orphan*/  v_lpf_int_y; int /*<<< orphan*/  v_typ_c; int /*<<< orphan*/  v_typ_y; int /*<<< orphan*/  v_flip; int /*<<< orphan*/  h_flip; scalar_t__ o_hsz; scalar_t__ o_vsz; } ;

/* Variables and functions */
 void* DISABLE ; 
 void* ENABLE ; 
 scalar_t__ RESIZER_OUTPUT_NONE ; 
 size_t RESIZER_PAD_SOURCE ; 
 int RSZ_A ; 
 int RSZ_B ; 

__attribute__((used)) static void
configure_resizer_out_params(struct vpfe_resizer_device *resizer, int index,
			     void *output_spec, unsigned char partial,
			     unsigned int flag)
{
	struct resizer_params *param = &resizer->config;
	struct v4l2_mbus_framefmt *outformat;
	struct vpfe_rsz_output_spec *output;

	if (index == RSZ_A &&
	    resizer->resizer_a.output == RESIZER_OUTPUT_NONE) {
		param->rsz_en[index] = DISABLE;
		return;
	}
	if (index == RSZ_B &&
	    resizer->resizer_b.output == RESIZER_OUTPUT_NONE) {
		param->rsz_en[index] = DISABLE;
		return;
	}
	output = output_spec;
	param->rsz_en[index] = ENABLE;
	if (partial) {
		param->rsz_rsc_param[index].h_flip = output->h_flip;
		param->rsz_rsc_param[index].v_flip = output->v_flip;
		param->rsz_rsc_param[index].v_typ_y = output->v_typ_y;
		param->rsz_rsc_param[index].v_typ_c = output->v_typ_c;
		param->rsz_rsc_param[index].v_lpf_int_y =
						output->v_lpf_int_y;
		param->rsz_rsc_param[index].v_lpf_int_c =
						output->v_lpf_int_c;
		param->rsz_rsc_param[index].h_typ_y = output->h_typ_y;
		param->rsz_rsc_param[index].h_typ_c = output->h_typ_c;
		param->rsz_rsc_param[index].h_lpf_int_y =
						output->h_lpf_int_y;
		param->rsz_rsc_param[index].h_lpf_int_c =
						output->h_lpf_int_c;
		param->rsz_rsc_param[index].dscale_en =
						output->en_down_scale;
		param->rsz_rsc_param[index].h_dscale_ave_sz =
						output->h_dscale_ave_sz;
		param->rsz_rsc_param[index].v_dscale_ave_sz =
						output->v_dscale_ave_sz;
		param->ext_mem_param[index].user_y_ofst =
				    (output->user_y_ofst + 31) & ~0x1f;
		param->ext_mem_param[index].user_c_ofst =
				    (output->user_c_ofst + 31) & ~0x1f;
		return;
	}

	if (index == RSZ_A)
		outformat = &resizer->resizer_a.formats[RESIZER_PAD_SOURCE];
	else
		outformat = &resizer->resizer_b.formats[RESIZER_PAD_SOURCE];
	param->rsz_rsc_param[index].o_vsz = outformat->height - 1;
	param->rsz_rsc_param[index].o_hsz = outformat->width - 1;
	param->ext_mem_param[index].rsz_sdr_ptr_s_y = output->vst_y;
	param->ext_mem_param[index].rsz_sdr_ptr_e_y = outformat->height;
	param->ext_mem_param[index].rsz_sdr_ptr_s_c = output->vst_c;
	param->ext_mem_param[index].rsz_sdr_ptr_e_c = outformat->height;

	if (!flag)
		return;
	/* update common parameters */
	param->rsz_rsc_param[index].h_flip = output->h_flip;
	param->rsz_rsc_param[index].v_flip = output->v_flip;
	param->rsz_rsc_param[index].v_typ_y = output->v_typ_y;
	param->rsz_rsc_param[index].v_typ_c = output->v_typ_c;
	param->rsz_rsc_param[index].v_lpf_int_y = output->v_lpf_int_y;
	param->rsz_rsc_param[index].v_lpf_int_c = output->v_lpf_int_c;
	param->rsz_rsc_param[index].h_typ_y = output->h_typ_y;
	param->rsz_rsc_param[index].h_typ_c = output->h_typ_c;
	param->rsz_rsc_param[index].h_lpf_int_y = output->h_lpf_int_y;
	param->rsz_rsc_param[index].h_lpf_int_c = output->h_lpf_int_c;
	param->rsz_rsc_param[index].dscale_en = output->en_down_scale;
	param->rsz_rsc_param[index].h_dscale_ave_sz = output->h_dscale_ave_sz;
	param->rsz_rsc_param[index].v_dscale_ave_sz = output->h_dscale_ave_sz;
	param->ext_mem_param[index].user_y_ofst =
					(output->user_y_ofst + 31) & ~0x1f;
	param->ext_mem_param[index].user_c_ofst =
					(output->user_c_ofst + 31) & ~0x1f;
}