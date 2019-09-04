#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/ * dev_addr; } ;
struct TYPE_5__ {int uc_count; scalar_t__ mc_count; int /*<<< orphan*/  group_prom; int /*<<< orphan*/ * uc_table; } ;
typedef  TYPE_1__ DFX_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ DFX_K_SUCCESS ; 
 int /*<<< orphan*/  FDDI_K_ALEN ; 
 scalar_t__ PI_CMD_ADDR_FILTER_K_SIZE ; 
 int /*<<< orphan*/  PI_FSTATE_K_PASS ; 
 scalar_t__ dfx_ctl_update_cam (TYPE_1__*) ; 
 scalar_t__ dfx_ctl_update_filters (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dfx_ctl_set_mac_address(struct net_device *dev, void *addr)
	{
	struct sockaddr	*p_sockaddr = (struct sockaddr *)addr;
	DFX_board_t *bp = netdev_priv(dev);

	/* Copy unicast address to driver-maintained structs and update count */

	memcpy(dev->dev_addr, p_sockaddr->sa_data, FDDI_K_ALEN);	/* update device struct */
	memcpy(&bp->uc_table[0], p_sockaddr->sa_data, FDDI_K_ALEN);	/* update driver struct */
	bp->uc_count = 1;

	/*
	 * Verify we're not exceeding the CAM size by adding unicast address
	 *
	 * Note: It's possible that before entering this routine we've
	 *       already filled the CAM with 62 multicast addresses.
	 *		 Since we need to place the node address override into
	 *		 the CAM, we have to check to see that we're not
	 *		 exceeding the CAM size.  If we are, we have to enable
	 *		 the LLC group (multicast) promiscuous mode filter as
	 *		 in dfx_ctl_set_multicast_list.
	 */

	if ((bp->uc_count + bp->mc_count) > PI_CMD_ADDR_FILTER_K_SIZE)
		{
		bp->group_prom	= PI_FSTATE_K_PASS;		/* Enable LLC group prom mode */
		bp->mc_count	= 0;					/* Don't add mc addrs to CAM */

		/* Update adapter filters */

		if (dfx_ctl_update_filters(bp) != DFX_K_SUCCESS)
			{
			DBG_printk("%s: Could not update adapter filters!\n", dev->name);
			}
		else
			{
			DBG_printk("%s: Adapter filters updated!\n", dev->name);
			}
		}

	/* Update adapter CAM with new unicast address */

	if (dfx_ctl_update_cam(bp) != DFX_K_SUCCESS)
		{
		DBG_printk("%s: Could not set new MAC address!\n", dev->name);
		}
	else
		{
		DBG_printk("%s: Adapter CAM updated with new MAC address\n", dev->name);
		}
	return 0;			/* always return zero */
	}