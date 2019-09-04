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
struct TYPE_2__ {scalar_t__ integer; scalar_t__ decimal; } ;
struct vpfe_ipipe_gic {int en; scalar_t__ gain; scalar_t__ thr; scalar_t__ slope; int apply_lsc_gain; TYPE_1__ nf2_thr_gain; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GIC_GAIN_MASK ; 
 scalar_t__ GIC_NFGAN_DECI_MASK ; 
 scalar_t__ GIC_NFGAN_INT_MASK ; 
 scalar_t__ GIC_SLOPE_MASK ; 
 scalar_t__ GIC_THR_MASK ; 

__attribute__((used)) static int ipipe_validate_gic_params(struct vpfe_ipipe_gic *gic)
{
	if (gic->en > 1 || gic->gain > GIC_GAIN_MASK ||
	    gic->thr > GIC_THR_MASK || gic->slope > GIC_SLOPE_MASK ||
	    gic->apply_lsc_gain > 1 ||
	    gic->nf2_thr_gain.integer > GIC_NFGAN_INT_MASK ||
	    gic->nf2_thr_gain.decimal > GIC_NFGAN_DECI_MASK)
		return -EINVAL;

	return 0;
}