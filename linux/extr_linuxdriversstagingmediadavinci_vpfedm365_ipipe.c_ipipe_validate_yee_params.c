#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vpfe_ipipe_yee {int en; int en_halo_red; scalar_t__ hpf_shft; scalar_t__ hpf_coef_00; scalar_t__ hpf_coef_01; scalar_t__ hpf_coef_02; scalar_t__ hpf_coef_10; scalar_t__ hpf_coef_11; scalar_t__ hpf_coef_12; scalar_t__ hpf_coef_20; scalar_t__ hpf_coef_21; scalar_t__ hpf_coef_22; scalar_t__ yee_thr; scalar_t__ es_gain; scalar_t__ es_thr1; scalar_t__ es_thr2; scalar_t__ es_gain_grad; scalar_t__ es_ofst_grad; scalar_t__* table; } ;

/* Variables and functions */
 int EINVAL ; 
 int VPFE_IPIPE_MAX_SIZE_YEE_LUT ; 
 scalar_t__ YEE_COEF_MASK ; 
 scalar_t__ YEE_ENTRY_MASK ; 
 scalar_t__ YEE_ES_GAIN_MASK ; 
 scalar_t__ YEE_ES_THR1_MASK ; 
 scalar_t__ YEE_HPF_SHIFT_MASK ; 
 scalar_t__ YEE_THR_MASK ; 

__attribute__((used)) static int ipipe_validate_yee_params(struct vpfe_ipipe_yee *yee)
{
	int i;

	if (yee->en > 1 ||
	    yee->en_halo_red > 1 ||
	    yee->hpf_shft > YEE_HPF_SHIFT_MASK)
		return -EINVAL;

	if (yee->hpf_coef_00 > YEE_COEF_MASK ||
	    yee->hpf_coef_01 > YEE_COEF_MASK ||
	    yee->hpf_coef_02 > YEE_COEF_MASK ||
	    yee->hpf_coef_10 > YEE_COEF_MASK ||
	    yee->hpf_coef_11 > YEE_COEF_MASK ||
	    yee->hpf_coef_12 > YEE_COEF_MASK ||
	    yee->hpf_coef_20 > YEE_COEF_MASK ||
	    yee->hpf_coef_21 > YEE_COEF_MASK ||
	    yee->hpf_coef_22 > YEE_COEF_MASK)
		return -EINVAL;

	if (yee->yee_thr > YEE_THR_MASK ||
	    yee->es_gain > YEE_ES_GAIN_MASK ||
	    yee->es_thr1 > YEE_ES_THR1_MASK ||
	    yee->es_thr2 > YEE_THR_MASK ||
	    yee->es_gain_grad > YEE_THR_MASK ||
	    yee->es_ofst_grad > YEE_THR_MASK)
		return -EINVAL;

	for (i = 0; i < VPFE_IPIPE_MAX_SIZE_YEE_LUT; i++)
		if (yee->table[i] > YEE_ENTRY_MASK)
			return -EINVAL;

	return 0;
}