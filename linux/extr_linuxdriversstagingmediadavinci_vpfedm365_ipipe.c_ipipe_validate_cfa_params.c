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
struct vpfe_ipipe_cfa {scalar_t__ hpf_thr_2dir; scalar_t__ hpf_slp_2dir; scalar_t__ hp_mix_thr_2dir; scalar_t__ hp_mix_slope_2dir; scalar_t__ dir_thr_2dir; scalar_t__ dir_slope_2dir; scalar_t__ nd_wt_2dir; scalar_t__ hue_fract_daa; scalar_t__ edge_thr_daa; scalar_t__ thr_min_daa; scalar_t__ thr_slope_daa; scalar_t__ slope_min_daa; scalar_t__ slope_slope_daa; scalar_t__ lp_wt_daa; } ;

/* Variables and functions */
 scalar_t__ CFA_DAA_EDG_THR_MASK ; 
 scalar_t__ CFA_DAA_HUE_FRA_MASK ; 
 scalar_t__ CFA_DAA_LP_WT_MASK ; 
 scalar_t__ CFA_DAA_SLP_MIN_MASK ; 
 scalar_t__ CFA_DAA_SLP_SLP_MASK ; 
 scalar_t__ CFA_DAA_THR_MIN_MASK ; 
 scalar_t__ CFA_DAA_THR_SLP_MASK ; 
 scalar_t__ CFA_DIR_SLP_2DIR_MASK ; 
 scalar_t__ CFA_DIR_THR_2DIR_MASK ; 
 scalar_t__ CFA_HPF_MIX_SLP_2DIR_MASK ; 
 scalar_t__ CFA_HPF_MIX_THR_2DIR_MASK ; 
 scalar_t__ CFA_HPF_SLOPE_2DIR_MASK ; 
 scalar_t__ CFA_HPF_THR_2DIR_MASK ; 
 scalar_t__ CFA_ND_WT_2DIR_MASK ; 
 int EINVAL ; 

__attribute__((used)) static int ipipe_validate_cfa_params(struct vpfe_ipipe_cfa *cfa)
{
	if (cfa->hpf_thr_2dir > CFA_HPF_THR_2DIR_MASK ||
	    cfa->hpf_slp_2dir > CFA_HPF_SLOPE_2DIR_MASK ||
	    cfa->hp_mix_thr_2dir > CFA_HPF_MIX_THR_2DIR_MASK ||
	    cfa->hp_mix_slope_2dir > CFA_HPF_MIX_SLP_2DIR_MASK ||
	    cfa->dir_thr_2dir > CFA_DIR_THR_2DIR_MASK ||
	    cfa->dir_slope_2dir > CFA_DIR_SLP_2DIR_MASK ||
	    cfa->nd_wt_2dir > CFA_ND_WT_2DIR_MASK ||
	    cfa->hue_fract_daa > CFA_DAA_HUE_FRA_MASK ||
	    cfa->edge_thr_daa > CFA_DAA_EDG_THR_MASK ||
	    cfa->thr_min_daa > CFA_DAA_THR_MIN_MASK ||
	    cfa->thr_slope_daa > CFA_DAA_THR_SLP_MASK ||
	    cfa->slope_min_daa > CFA_DAA_SLP_MIN_MASK ||
	    cfa->slope_slope_daa > CFA_DAA_SLP_SLP_MASK ||
	    cfa->lp_wt_daa > CFA_DAA_LP_WT_MASK)
		return -EINVAL;

	return 0;
}