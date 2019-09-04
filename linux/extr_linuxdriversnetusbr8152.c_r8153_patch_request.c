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
typedef  int u16 ;
struct r8152 {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  OCP_PHY_PATCH_CMD ; 
 int /*<<< orphan*/  OCP_PHY_PATCH_STAT ; 
 int PATCH_READY ; 
 int PATCH_REQUEST ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ocp_reg_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_reg_write (struct r8152*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int r8153_patch_request(struct r8152 *tp, bool request)
{
	u16 data;
	int i;

	data = ocp_reg_read(tp, OCP_PHY_PATCH_CMD);
	if (request)
		data |= PATCH_REQUEST;
	else
		data &= ~PATCH_REQUEST;
	ocp_reg_write(tp, OCP_PHY_PATCH_CMD, data);

	for (i = 0; request && i < 5000; i++) {
		usleep_range(1000, 2000);
		if (ocp_reg_read(tp, OCP_PHY_PATCH_STAT) & PATCH_READY)
			break;
	}

	if (request && !(ocp_reg_read(tp, OCP_PHY_PATCH_STAT) & PATCH_READY)) {
		netif_err(tp, drv, tp->netdev, "patch request fail\n");
		r8153_patch_request(tp, false);
		return -ETIME;
	} else {
		return 0;
	}
}