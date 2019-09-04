#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vpfe_ipipe_yee {int /*<<< orphan*/  table; int /*<<< orphan*/  es_ofst_grad; int /*<<< orphan*/  es_gain_grad; int /*<<< orphan*/  es_thr2; int /*<<< orphan*/  es_thr1; int /*<<< orphan*/  es_gain; int /*<<< orphan*/  yee_thr; int /*<<< orphan*/  hpf_coef_22; int /*<<< orphan*/  hpf_coef_21; int /*<<< orphan*/  hpf_coef_20; int /*<<< orphan*/  hpf_coef_12; int /*<<< orphan*/  hpf_coef_11; int /*<<< orphan*/  hpf_coef_10; int /*<<< orphan*/  hpf_coef_02; int /*<<< orphan*/  hpf_coef_01; int /*<<< orphan*/  hpf_coef_00; int /*<<< orphan*/  hpf_shft; int /*<<< orphan*/  merge_meth; int /*<<< orphan*/  en_halo_red; int /*<<< orphan*/  en; } ;
struct TYPE_2__ {struct vpfe_ipipe_yee yee; } ;
struct vpfe_ipipe_device {TYPE_1__ config; } ;

/* Variables and functions */
 int VPFE_IPIPE_MAX_SIZE_YEE_LUT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ipipe_get_yee_params(struct vpfe_ipipe_device *ipipe, void *param)
{
	struct vpfe_ipipe_yee *yee_param = param;
	struct vpfe_ipipe_yee *yee = &ipipe->config.yee;

	yee_param->en = yee->en;
	yee_param->en_halo_red = yee->en_halo_red;
	yee_param->merge_meth = yee->merge_meth;
	yee_param->hpf_shft = yee->hpf_shft;
	yee_param->hpf_coef_00 = yee->hpf_coef_00;
	yee_param->hpf_coef_01 = yee->hpf_coef_01;
	yee_param->hpf_coef_02 = yee->hpf_coef_02;
	yee_param->hpf_coef_10 = yee->hpf_coef_10;
	yee_param->hpf_coef_11 = yee->hpf_coef_11;
	yee_param->hpf_coef_12 = yee->hpf_coef_12;
	yee_param->hpf_coef_20 = yee->hpf_coef_20;
	yee_param->hpf_coef_21 = yee->hpf_coef_21;
	yee_param->hpf_coef_22 = yee->hpf_coef_22;
	yee_param->yee_thr = yee->yee_thr;
	yee_param->es_gain = yee->es_gain;
	yee_param->es_thr1 = yee->es_thr1;
	yee_param->es_thr2 = yee->es_thr2;
	yee_param->es_gain_grad = yee->es_gain_grad;
	yee_param->es_ofst_grad = yee->es_ofst_grad;
	memcpy(yee_param->table, &yee->table,
	       (VPFE_IPIPE_MAX_SIZE_YEE_LUT * sizeof(short)));

	return 0;
}