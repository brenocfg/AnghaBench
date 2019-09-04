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
typedef  int u32 ;
struct renesas_usb3_request {int dummy; } ;
struct renesas_usb3_ep {int started; int /*<<< orphan*/  num; scalar_t__ dir_in; scalar_t__ halt; } ;
struct renesas_usb3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int PN_INT_BFRDY ; 
 int PN_INT_LSTTR ; 
 int /*<<< orphan*/  USB3_PN_INT_ENA ; 
 int /*<<< orphan*/  USB3_PN_WRITE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ usb3_dma_try_start (struct renesas_usb3_ep*,struct renesas_usb3_request*) ; 
 int /*<<< orphan*/  usb3_enable_pipe_irq (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 struct renesas_usb3_request* usb3_get_request (struct renesas_usb3_ep*) ; 
 scalar_t__ usb3_pn_change (struct renesas_usb3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_pn_start (struct renesas_usb3*) ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 
 int usb3_write_pipe (struct renesas_usb3_ep*,struct renesas_usb3_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_start_pipen(struct renesas_usb3_ep *usb3_ep,
			     struct renesas_usb3_request *usb3_req)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	struct renesas_usb3_request *usb3_req_first = usb3_get_request(usb3_ep);
	unsigned long flags;
	int ret = -EAGAIN;
	u32 enable_bits = 0;

	spin_lock_irqsave(&usb3->lock, flags);
	if (usb3_ep->halt || usb3_ep->started)
		goto out;
	if (usb3_req != usb3_req_first)
		goto out;

	if (usb3_pn_change(usb3, usb3_ep->num) < 0)
		goto out;

	usb3_ep->started = true;

	if (usb3_dma_try_start(usb3_ep, usb3_req))
		goto out;

	usb3_pn_start(usb3);

	if (usb3_ep->dir_in) {
		ret = usb3_write_pipe(usb3_ep, usb3_req, USB3_PN_WRITE);
		enable_bits |= PN_INT_LSTTR;
	}

	if (ret < 0)
		enable_bits |= PN_INT_BFRDY;

	if (enable_bits) {
		usb3_set_bit(usb3, enable_bits, USB3_PN_INT_ENA);
		usb3_enable_pipe_irq(usb3, usb3_ep->num);
	}
out:
	spin_unlock_irqrestore(&usb3->lock, flags);
}