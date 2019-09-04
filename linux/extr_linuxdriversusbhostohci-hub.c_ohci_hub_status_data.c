#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct usb_hcd {int /*<<< orphan*/  flags; } ;
struct ohci_hcd {int flags; int num_ports; int /*<<< orphan*/  lock; TYPE_2__* regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  a; } ;
struct TYPE_4__ {int /*<<< orphan*/  intrstatus; TYPE_1__ roothub; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCD_FLAG_POLL_RH ; 
 int /*<<< orphan*/  HCD_HW_ACCESSIBLE (struct usb_hcd*) ; 
 int MAX_ROOT_PORTS ; 
 int OHCI_INTR_RHSC ; 
 int OHCI_QUIRK_AMD756 ; 
 int RH_A_NDP ; 
 int RH_HS_LPSC ; 
 int RH_HS_OCIC ; 
 int RH_PS_CCS ; 
 int RH_PS_CSC ; 
 int RH_PS_OCIC ; 
 int RH_PS_PESC ; 
 int RH_PS_PRSC ; 
 int RH_PS_PSSC ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ohci_hcd* hcd_to_ohci (struct usb_hcd*) ; 
 int ohci_readl (struct ohci_hcd*,int /*<<< orphan*/ *) ; 
 scalar_t__ ohci_root_hub_state_changes (struct ohci_hcd*,int,int,int) ; 
 int /*<<< orphan*/  ohci_warn (struct ohci_hcd*,char*,int) ; 
 int /*<<< orphan*/  ohci_writel (struct ohci_hcd*,int,int /*<<< orphan*/ *) ; 
 int roothub_a (struct ohci_hcd*) ; 
 int roothub_portstatus (struct ohci_hcd*,int) ; 
 int roothub_status (struct ohci_hcd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ohci_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct ohci_hcd	*ohci = hcd_to_ohci (hcd);
	int		i, changed = 0, length = 1;
	int		any_connected = 0;
	int		rhsc_status;
	unsigned long	flags;

	spin_lock_irqsave (&ohci->lock, flags);
	if (!HCD_HW_ACCESSIBLE(hcd))
		goto done;

	/* undocumented erratum seen on at least rev D */
	if ((ohci->flags & OHCI_QUIRK_AMD756)
			&& (roothub_a (ohci) & RH_A_NDP) > MAX_ROOT_PORTS) {
		ohci_warn (ohci, "bogus NDP, rereads as NDP=%d\n",
			  ohci_readl (ohci, &ohci->regs->roothub.a) & RH_A_NDP);
		/* retry later; "should not happen" */
		goto done;
	}

	/* init status */
	if (roothub_status (ohci) & (RH_HS_LPSC | RH_HS_OCIC))
		buf [0] = changed = 1;
	else
		buf [0] = 0;
	if (ohci->num_ports > 7) {
		buf [1] = 0;
		length++;
	}

	/* Clear the RHSC status flag before reading the port statuses */
	ohci_writel(ohci, OHCI_INTR_RHSC, &ohci->regs->intrstatus);
	rhsc_status = ohci_readl(ohci, &ohci->regs->intrstatus) &
			OHCI_INTR_RHSC;

	/* look at each port */
	for (i = 0; i < ohci->num_ports; i++) {
		u32	status = roothub_portstatus (ohci, i);

		/* can't autostop if ports are connected */
		any_connected |= (status & RH_PS_CCS);

		if (status & (RH_PS_CSC | RH_PS_PESC | RH_PS_PSSC
				| RH_PS_OCIC | RH_PS_PRSC)) {
			changed = 1;
			if (i < 7)
			    buf [0] |= 1 << (i + 1);
			else
			    buf [1] |= 1 << (i - 7);
		}
	}

	if (ohci_root_hub_state_changes(ohci, changed,
			any_connected, rhsc_status))
		set_bit(HCD_FLAG_POLL_RH, &hcd->flags);
	else
		clear_bit(HCD_FLAG_POLL_RH, &hcd->flags);


done:
	spin_unlock_irqrestore (&ohci->lock, flags);

	return changed ? length : 0;
}