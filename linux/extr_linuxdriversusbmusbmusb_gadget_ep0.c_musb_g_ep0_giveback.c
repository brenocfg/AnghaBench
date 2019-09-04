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
struct usb_request {int dummy; } ;
struct musb {TYPE_1__* endpoints; } ;
struct TYPE_2__ {int /*<<< orphan*/  ep_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  musb_g_giveback (int /*<<< orphan*/ *,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void musb_g_ep0_giveback(struct musb *musb, struct usb_request *req)
{
	musb_g_giveback(&musb->endpoints[0].ep_in, req, 0);
}