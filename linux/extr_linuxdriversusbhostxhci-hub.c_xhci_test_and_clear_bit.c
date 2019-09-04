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
struct xhci_port {int /*<<< orphan*/  addr; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int xhci_port_state_to_neutral (int) ; 

void xhci_test_and_clear_bit(struct xhci_hcd *xhci, struct xhci_port *port,
			     u32 port_bit)
{
	u32 temp;

	temp = readl(port->addr);
	if (temp & port_bit) {
		temp = xhci_port_state_to_neutral(temp);
		temp |= port_bit;
		writel(temp, port->addr);
	}
}