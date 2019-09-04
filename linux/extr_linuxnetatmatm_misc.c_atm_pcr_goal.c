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
struct atm_trafprm {int pcr; int min_pcr; int max_pcr; } ;

/* Variables and functions */
 int ATM_MAX_PCR ; 

int atm_pcr_goal(const struct atm_trafprm *tp)
{
	if (tp->pcr && tp->pcr != ATM_MAX_PCR)
		return -tp->pcr;
	if (tp->min_pcr && !tp->pcr)
		return tp->min_pcr;
	if (tp->max_pcr != ATM_MAX_PCR)
		return -tp->max_pcr;
	return 0;
}