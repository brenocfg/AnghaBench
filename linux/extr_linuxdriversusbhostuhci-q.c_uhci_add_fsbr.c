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
struct urb_priv {int fsbr; } ;
struct urb {struct urb_priv* hcpriv; } ;
struct uhci_hcd {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void uhci_add_fsbr(struct uhci_hcd *uhci, struct urb *urb)
{
	struct urb_priv *urbp = urb->hcpriv;

	urbp->fsbr = 1;
}