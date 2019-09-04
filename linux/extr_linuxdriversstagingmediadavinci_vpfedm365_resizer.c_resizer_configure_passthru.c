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
struct TYPE_6__ {int /*<<< orphan*/  passthrough; } ;
struct resizer_params {TYPE_3__ rsz_common; TYPE_2__* rsz_rsc_param; void** rsz_en; TYPE_1__* rsz2rgb; } ;
struct vpfe_resizer_device {struct resizer_params config; } ;
struct TYPE_5__ {int v_dif; int h_dif; scalar_t__ i_hps; scalar_t__ i_vps; void* dscale_en; scalar_t__ h_lpf_int_c; scalar_t__ h_lpf_int_y; scalar_t__ h_phs; scalar_t__ v_lpf_int_c; scalar_t__ v_lpf_int_y; scalar_t__ v_phs_c; scalar_t__ v_phs_y; void* yen; void* cen; } ;
struct TYPE_4__ {void* rgb_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYPASS_ON ; 
 void* DISABLE ; 
 void* ENABLE ; 
 size_t RSZ_A ; 
 size_t RSZ_B ; 

__attribute__((used)) static void
resizer_configure_passthru(struct vpfe_resizer_device *resizer, int bypass)
{
	struct resizer_params *param = &resizer->config;

	param->rsz_rsc_param[RSZ_A].cen = DISABLE;
	param->rsz_rsc_param[RSZ_A].yen = DISABLE;
	param->rsz_rsc_param[RSZ_A].v_phs_y = 0;
	param->rsz_rsc_param[RSZ_A].v_phs_c = 0;
	param->rsz_rsc_param[RSZ_A].v_dif = 256;
	param->rsz_rsc_param[RSZ_A].v_lpf_int_y = 0;
	param->rsz_rsc_param[RSZ_A].v_lpf_int_c = 0;
	param->rsz_rsc_param[RSZ_A].h_phs = 0;
	param->rsz_rsc_param[RSZ_A].h_dif = 256;
	param->rsz_rsc_param[RSZ_A].h_lpf_int_y = 0;
	param->rsz_rsc_param[RSZ_A].h_lpf_int_c = 0;
	param->rsz_rsc_param[RSZ_A].dscale_en = DISABLE;
	param->rsz2rgb[RSZ_A].rgb_en = DISABLE;
	param->rsz_en[RSZ_A] = ENABLE;
	param->rsz_en[RSZ_B] = DISABLE;
	if (bypass) {
		param->rsz_rsc_param[RSZ_A].i_vps = 0;
		param->rsz_rsc_param[RSZ_A].i_hps = 0;
		/* Raw Bypass */
		param->rsz_common.passthrough = BYPASS_ON;
	}
}