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
typedef  scalar_t__ u8 ;
struct musb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_cppi_enabled (struct musb*) ; 
 scalar_t__ is_host_active (struct musb*) ; 
 int /*<<< orphan*/  musb_g_ep0_irq (struct musb*) ; 
 int /*<<< orphan*/  musb_g_rx (struct musb*,scalar_t__) ; 
 int /*<<< orphan*/  musb_g_tx (struct musb*,scalar_t__) ; 
 int /*<<< orphan*/  musb_h_ep0_irq (struct musb*) ; 
 int /*<<< orphan*/  musb_host_rx (struct musb*,scalar_t__) ; 
 int /*<<< orphan*/  musb_host_tx (struct musb*,scalar_t__) ; 

void musb_dma_completion(struct musb *musb, u8 epnum, u8 transmit)
{
	/* called with controller lock already held */

	if (!epnum) {
		if (!is_cppi_enabled(musb)) {
			/* endpoint 0 */
			if (is_host_active(musb))
				musb_h_ep0_irq(musb);
			else
				musb_g_ep0_irq(musb);
		}
	} else {
		/* endpoints 1..15 */
		if (transmit) {
			if (is_host_active(musb))
				musb_host_tx(musb, epnum);
			else
				musb_g_tx(musb, epnum);
		} else {
			/* receive */
			if (is_host_active(musb))
				musb_host_rx(musb, epnum);
			else
				musb_g_rx(musb, epnum);
		}
	}
}