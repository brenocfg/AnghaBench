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
struct vpfe_ipipe_otfdpc_3_0_cfg {scalar_t__ act_adj_shf; scalar_t__ det_thr; scalar_t__ det_slp; scalar_t__ det_thr_min; scalar_t__ det_thr_max; scalar_t__ corr_thr; scalar_t__ corr_slp; scalar_t__ corr_thr_min; scalar_t__ corr_thr_max; } ;
struct TYPE_5__ {scalar_t__ r; scalar_t__ gr; scalar_t__ gb; scalar_t__ b; } ;
struct TYPE_4__ {scalar_t__ r; scalar_t__ gr; scalar_t__ gb; scalar_t__ b; } ;
struct vpfe_ipipe_otfdpc_2_0_cfg {TYPE_2__ corr_thr; TYPE_1__ det_thr; } ;
struct TYPE_6__ {struct vpfe_ipipe_otfdpc_3_0_cfg dpc_3_0; struct vpfe_ipipe_otfdpc_2_0_cfg dpc_2_0; } ;
struct vpfe_ipipe_otfdpc {int en; scalar_t__ alg; TYPE_3__ alg_cfg; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OTFDPC_DPC2_THR_MASK ; 
 scalar_t__ OTF_DPC3_0_CORR_MASK ; 
 scalar_t__ OTF_DPC3_0_DET_MASK ; 
 scalar_t__ OTF_DPC3_0_SHF_MASK ; 
 scalar_t__ OTF_DPC3_0_SLP_MASK ; 
 scalar_t__ VPFE_IPIPE_OTFDPC_2_0 ; 

__attribute__((used)) static int ipipe_validate_otfdpc_params(struct vpfe_ipipe_otfdpc *dpc_param)
{
	struct vpfe_ipipe_otfdpc_2_0_cfg *dpc_2_0;
	struct vpfe_ipipe_otfdpc_3_0_cfg *dpc_3_0;

	if (dpc_param->en > 1)
		return -EINVAL;

	if (dpc_param->alg == VPFE_IPIPE_OTFDPC_2_0) {
		dpc_2_0 = &dpc_param->alg_cfg.dpc_2_0;
		if (dpc_2_0->det_thr.r > OTFDPC_DPC2_THR_MASK ||
		    dpc_2_0->det_thr.gr > OTFDPC_DPC2_THR_MASK ||
		    dpc_2_0->det_thr.gb > OTFDPC_DPC2_THR_MASK ||
		    dpc_2_0->det_thr.b > OTFDPC_DPC2_THR_MASK ||
		    dpc_2_0->corr_thr.r > OTFDPC_DPC2_THR_MASK ||
		    dpc_2_0->corr_thr.gr > OTFDPC_DPC2_THR_MASK ||
		    dpc_2_0->corr_thr.gb > OTFDPC_DPC2_THR_MASK ||
		    dpc_2_0->corr_thr.b > OTFDPC_DPC2_THR_MASK)
			return -EINVAL;
		return 0;
	}

	dpc_3_0 = &dpc_param->alg_cfg.dpc_3_0;

	if (dpc_3_0->act_adj_shf > OTF_DPC3_0_SHF_MASK ||
	    dpc_3_0->det_thr > OTF_DPC3_0_DET_MASK ||
	    dpc_3_0->det_slp > OTF_DPC3_0_SLP_MASK ||
	    dpc_3_0->det_thr_min > OTF_DPC3_0_DET_MASK ||
	    dpc_3_0->det_thr_max > OTF_DPC3_0_DET_MASK ||
	    dpc_3_0->corr_thr > OTF_DPC3_0_CORR_MASK ||
	    dpc_3_0->corr_slp > OTF_DPC3_0_SLP_MASK ||
	    dpc_3_0->corr_thr_min > OTF_DPC3_0_CORR_MASK ||
	    dpc_3_0->corr_thr_max > OTF_DPC3_0_CORR_MASK)
		return -EINVAL;

	return 0;
}