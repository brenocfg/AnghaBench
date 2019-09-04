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
struct usbnet {TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  cur_altsetting; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 scalar_t__ cdc_ncm_comm_intf_is_mbim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdc_ncm_eth_hlen(struct usbnet *dev)
{
	if (cdc_ncm_comm_intf_is_mbim(dev->intf->cur_altsetting))
		return 0;
	return ETH_HLEN;
}