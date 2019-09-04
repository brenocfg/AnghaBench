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
struct urb_priv {scalar_t__ tds_cnt; scalar_t__ num_of_tds; scalar_t__ state; } ;
struct urb {struct urb_priv* hcpriv; } ;
struct td {struct ed* ed; struct urb* urb; } ;
struct fhci_hcd {TYPE_1__* timer; int /*<<< orphan*/  lock; int /*<<< orphan*/  hc_list; } ;
struct ed {scalar_t__ state; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ FHCI_ED_HALTED ; 
 void* FHCI_ED_OPER ; 
 scalar_t__ FHCI_ED_SKIP ; 
 scalar_t__ FHCI_ED_URB_DEL ; 
 scalar_t__ URB_DEL ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fhci_del_ed_list (struct fhci_hcd*,struct ed*) ; 
 int /*<<< orphan*/  fhci_done_td (struct urb*,struct td*) ; 
 struct td* fhci_remove_td_from_done_list (int /*<<< orphan*/ ) ; 
 TYPE_2__* fhci_to_hcd (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_urb_complete_free (struct fhci_hcd*,struct urb*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_done_list(unsigned long data)
{
	struct urb *urb;
	struct ed *ed;
	struct td *td;
	struct urb_priv *urb_priv;
	struct fhci_hcd *fhci = (struct fhci_hcd *)data;

	disable_irq(fhci->timer->irq);
	disable_irq(fhci_to_hcd(fhci)->irq);
	spin_lock(&fhci->lock);

	td = fhci_remove_td_from_done_list(fhci->hc_list);
	while (td != NULL) {
		urb = td->urb;
		urb_priv = urb->hcpriv;
		ed = td->ed;

		/* update URB's length and status from TD */
		fhci_done_td(urb, td);
		urb_priv->tds_cnt++;

		/*
		 * if all this urb's TDs are done, call complete()
		 * Interrupt transfers are the onley special case:
		 * they are reissued,until "deleted" by usb_unlink_urb
		 * (real work done in a SOF intr, by process_del_list)
		 */
		if (urb_priv->tds_cnt == urb_priv->num_of_tds) {
			fhci_urb_complete_free(fhci, urb);
		} else if (urb_priv->state == URB_DEL &&
				ed->state == FHCI_ED_SKIP) {
			fhci_del_ed_list(fhci, ed);
			ed->state = FHCI_ED_OPER;
		} else if (ed->state == FHCI_ED_HALTED) {
			urb_priv->state = URB_DEL;
			ed->state = FHCI_ED_URB_DEL;
			fhci_del_ed_list(fhci, ed);
			ed->state = FHCI_ED_OPER;
		}

		td = fhci_remove_td_from_done_list(fhci->hc_list);
	}

	spin_unlock(&fhci->lock);
	enable_irq(fhci->timer->irq);
	enable_irq(fhci_to_hcd(fhci)->irq);
}