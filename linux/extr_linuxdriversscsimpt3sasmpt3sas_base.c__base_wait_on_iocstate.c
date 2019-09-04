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
typedef  int u32 ;
struct MPT3SAS_ADAPTER {int dummy; } ;

/* Variables and functions */
 int MPI2_IOC_STATE_FAULT ; 
 int mpt3sas_base_get_iocstate (struct MPT3SAS_ADAPTER*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
_base_wait_on_iocstate(struct MPT3SAS_ADAPTER *ioc, u32 ioc_state, int timeout)
{
	u32 count, cntdn;
	u32 current_state;

	count = 0;
	cntdn = 1000 * timeout;
	do {
		current_state = mpt3sas_base_get_iocstate(ioc, 1);
		if (current_state == ioc_state)
			return 0;
		if (count && current_state == MPI2_IOC_STATE_FAULT)
			break;

		usleep_range(1000, 1500);
		count++;
	} while (--cntdn);

	return current_state;
}