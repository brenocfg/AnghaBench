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
struct at91_udc {struct at91_ep* ep; } ;
struct at91_ep {int maxpacket; } ;

/* Variables and functions */
 int NUM_ENDPOINTS ; 

__attribute__((used)) static int at91sam9263_udc_init(struct at91_udc *udc)
{
	struct at91_ep *ep;
	int i;

	for (i = 0; i < NUM_ENDPOINTS; i++) {
		ep = &udc->ep[i];

		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3:
			ep->maxpacket = 64;
			break;
		case 4:
		case 5:
			ep->maxpacket = 256;
			break;
		}
	}

	return 0;
}