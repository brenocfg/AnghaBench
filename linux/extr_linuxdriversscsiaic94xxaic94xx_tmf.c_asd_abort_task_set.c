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
typedef  int /*<<< orphan*/  u8 ;
struct domain_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMF_ABORT_TASK_SET ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int /*<<< orphan*/  asd_clear_nexus_I_T_L (struct domain_device*,int /*<<< orphan*/ *) ; 
 int asd_initiate_ssp_tmf (struct domain_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int asd_abort_task_set(struct domain_device *dev, u8 *lun)
{
	int res = asd_initiate_ssp_tmf(dev, lun, TMF_ABORT_TASK_SET, 0);

	if (res == TMF_RESP_FUNC_COMPLETE)
		asd_clear_nexus_I_T_L(dev, lun);
	return res;
}