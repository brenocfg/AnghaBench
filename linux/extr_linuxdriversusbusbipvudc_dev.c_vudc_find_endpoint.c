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
typedef  int u8 ;
struct vudc {struct vep* ep; } ;
struct vep {TYPE_1__* desc; } ;
struct TYPE_2__ {int bEndpointAddress; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int VIRTUAL_ENDPOINTS ; 

struct vep *vudc_find_endpoint(struct vudc *udc, u8 address)
{
	int i;

	if ((address & ~USB_DIR_IN) == 0)
		return &udc->ep[0];

	for (i = 1; i < VIRTUAL_ENDPOINTS; i++) {
		struct vep *ep = &udc->ep[i];

		if (!ep->desc)
			continue;
		if (ep->desc->bEndpointAddress == address)
			return ep;
	}
	return NULL;
}