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

/* Variables and functions */
 int TM_CAUSE_KVM_FAC_UNAV ; 
 int TM_CAUSE_KVM_RESCHED ; 
 int TM_CAUSE_RESCHED ; 
 int failure_code () ; 

__attribute__((used)) static inline bool failure_is_reschedule(void)
{
	if ((failure_code() & TM_CAUSE_RESCHED) == TM_CAUSE_RESCHED ||
	    (failure_code() & TM_CAUSE_KVM_RESCHED) == TM_CAUSE_KVM_RESCHED ||
	    (failure_code() & TM_CAUSE_KVM_FAC_UNAV) == TM_CAUSE_KVM_FAC_UNAV)
		return true;

	return false;
}