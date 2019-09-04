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
struct TYPE_2__ {unsigned int maxpacket; } ;
struct dwc2_hsotg_ep {int index; TYPE_1__ ep; scalar_t__ dir_in; } ;

/* Variables and functions */
 int DIEPTSIZ0_PKTCNT_LIMIT ; 
 int DXEPTSIZ_PKTCNT_LIMIT ; 
 int DXEPTSIZ_XFERSIZE_LIMIT ; 

__attribute__((used)) static unsigned int get_ep_limit(struct dwc2_hsotg_ep *hs_ep)
{
	int index = hs_ep->index;
	unsigned int maxsize;
	unsigned int maxpkt;

	if (index != 0) {
		maxsize = DXEPTSIZ_XFERSIZE_LIMIT + 1;
		maxpkt = DXEPTSIZ_PKTCNT_LIMIT + 1;
	} else {
		maxsize = 64 + 64;
		if (hs_ep->dir_in)
			maxpkt = DIEPTSIZ0_PKTCNT_LIMIT + 1;
		else
			maxpkt = 2;
	}

	/* we made the constant loading easier above by using +1 */
	maxpkt--;
	maxsize--;

	/*
	 * constrain by packet count if maxpkts*pktsize is greater
	 * than the length register size.
	 */

	if ((maxpkt * hs_ep->ep.maxpacket) < maxsize)
		maxsize = maxpkt * hs_ep->ep.maxpacket;

	return maxsize;
}