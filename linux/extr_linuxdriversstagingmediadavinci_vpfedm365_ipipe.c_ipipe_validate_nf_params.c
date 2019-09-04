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
struct vpfe_ipipe_nf {int en; scalar_t__ shft_val; scalar_t__ spread_val; int apply_lsc_gain; scalar_t__ edge_det_min_thr; scalar_t__ edge_det_max_thr; scalar_t__* thr; scalar_t__* str; } ;

/* Variables and functions */
 scalar_t__ D2F_EDGE_DET_THR_MASK ; 
 scalar_t__ D2F_SHFT_VAL_MASK ; 
 scalar_t__ D2F_SPR_VAL_MASK ; 
 scalar_t__ D2F_STR_VAL_MASK ; 
 scalar_t__ D2F_THR_VAL_MASK ; 
 int EINVAL ; 
 int VPFE_IPIPE_NF_STR_TABLE_SIZE ; 
 int VPFE_IPIPE_NF_THR_TABLE_SIZE ; 

__attribute__((used)) static int ipipe_validate_nf_params(struct vpfe_ipipe_nf *nf_param)
{
	int i;

	if (nf_param->en > 1 || nf_param->shft_val > D2F_SHFT_VAL_MASK ||
	    nf_param->spread_val > D2F_SPR_VAL_MASK ||
	    nf_param->apply_lsc_gain > 1 ||
	    nf_param->edge_det_min_thr > D2F_EDGE_DET_THR_MASK ||
	    nf_param->edge_det_max_thr > D2F_EDGE_DET_THR_MASK)
		return -EINVAL;

	for (i = 0; i < VPFE_IPIPE_NF_THR_TABLE_SIZE; i++)
		if (nf_param->thr[i] > D2F_THR_VAL_MASK)
			return -EINVAL;

	for (i = 0; i < VPFE_IPIPE_NF_STR_TABLE_SIZE; i++)
		if (nf_param->str[i] > D2F_STR_VAL_MASK)
			return -EINVAL;

	return 0;
}