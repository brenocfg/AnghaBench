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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCC ; 
 int /*<<< orphan*/  CCC_OPC ; 
 int /*<<< orphan*/  CCC_OPC_CONFIG ; 
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  CSR_OPS ; 
 int /*<<< orphan*/  CSR_OPS_CONFIG ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  ravb_modify (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ravb_wait (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_config(struct net_device *ndev)
{
	int error;

	/* Set config mode */
	ravb_modify(ndev, CCC, CCC_OPC, CCC_OPC_CONFIG);
	/* Check if the operating mode is changed to the config mode */
	error = ravb_wait(ndev, CSR, CSR_OPS, CSR_OPS_CONFIG);
	if (error)
		netdev_err(ndev, "failed to switch device to config mode\n");

	return error;
}