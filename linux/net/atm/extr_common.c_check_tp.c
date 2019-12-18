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
struct atm_trafprm {scalar_t__ traffic_class; scalar_t__ min_pcr; scalar_t__ max_pcr; int /*<<< orphan*/  pcr; } ;

/* Variables and functions */
 scalar_t__ ATM_ANYCLASS ; 
 scalar_t__ ATM_MAX_PCR ; 
 scalar_t__ ATM_UBR ; 
 int EINVAL ; 

__attribute__((used)) static int check_tp(const struct atm_trafprm *tp)
{
	/* @@@ Should be merged with adjust_tp */
	if (!tp->traffic_class || tp->traffic_class == ATM_ANYCLASS)
		return 0;
	if (tp->traffic_class != ATM_UBR && !tp->min_pcr && !tp->pcr &&
	    !tp->max_pcr)
		return -EINVAL;
	if (tp->min_pcr == ATM_MAX_PCR)
		return -EINVAL;
	if (tp->min_pcr && tp->max_pcr && tp->max_pcr != ATM_MAX_PCR &&
	    tp->min_pcr > tp->max_pcr)
		return -EINVAL;
	/*
	 * We allow pcr to be outside [min_pcr,max_pcr], because later
	 * adjustment may still push it in the valid range.
	 */
	return 0;
}