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
typedef  int /*<<< orphan*/  u32 ;
struct usbnet {TYPE_1__* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  cur_altsetting; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDC_MBIM_MIN_DATAGRAM_SIZE ; 
 int /*<<< orphan*/  CDC_NCM_MIN_DATAGRAM_SIZE ; 
 scalar_t__ cdc_ncm_comm_intf_is_mbim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cdc_ncm_min_dgram_size(struct usbnet *dev)
{
	if (cdc_ncm_comm_intf_is_mbim(dev->intf->cur_altsetting))
		return CDC_MBIM_MIN_DATAGRAM_SIZE;
	return CDC_NCM_MIN_DATAGRAM_SIZE;
}