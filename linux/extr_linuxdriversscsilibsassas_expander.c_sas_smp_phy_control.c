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
typedef  int u8 ;
struct sas_phy_linkrates {int minimum_linkrate; int maximum_linkrate; } ;
struct domain_device {int dummy; } ;
typedef  enum phy_func { ____Placeholder_phy_func } phy_func ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PC_REQ_SIZE ; 
 int /*<<< orphan*/  PC_RESP_SIZE ; 
 int SMP_PHY_CONTROL ; 
 int* alloc_smp_req (int /*<<< orphan*/ ) ; 
 int* alloc_smp_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int smp_execute_task (struct domain_device*,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int sas_smp_phy_control(struct domain_device *dev, int phy_id,
			enum phy_func phy_func,
			struct sas_phy_linkrates *rates)
{
	u8 *pc_req;
	u8 *pc_resp;
	int res;

	pc_req = alloc_smp_req(PC_REQ_SIZE);
	if (!pc_req)
		return -ENOMEM;

	pc_resp = alloc_smp_resp(PC_RESP_SIZE);
	if (!pc_resp) {
		kfree(pc_req);
		return -ENOMEM;
	}

	pc_req[1] = SMP_PHY_CONTROL;
	pc_req[9] = phy_id;
	pc_req[10]= phy_func;
	if (rates) {
		pc_req[32] = rates->minimum_linkrate << 4;
		pc_req[33] = rates->maximum_linkrate << 4;
	}

	res = smp_execute_task(dev, pc_req, PC_REQ_SIZE, pc_resp,PC_RESP_SIZE);

	kfree(pc_resp);
	kfree(pc_req);
	return res;
}