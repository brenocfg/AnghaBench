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
typedef  int /*<<< orphan*/  u32 ;
struct xhci_hcd {int dummy; } ;
struct xhci_command {int dummy; } ;

/* Variables and functions */
 int queue_command (struct xhci_hcd*,struct xhci_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int xhci_queue_vendor_command(struct xhci_hcd *xhci, struct xhci_command *cmd,
		u32 field1, u32 field2, u32 field3, u32 field4)
{
	return queue_command(xhci, cmd, field1, field2, field3, field4, false);
}