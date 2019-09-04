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
struct urb {struct c67x00_urb_priv* hcpriv; } ;
struct c67x00_urb_priv {int status; int /*<<< orphan*/  hep_node; } ;
struct c67x00_hcd {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  c67x00_hcd_to_hcd (struct c67x00_hcd*) ; 
 int /*<<< orphan*/  c67x00_release_urb (struct c67x00_hcd*,struct urb*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (int /*<<< orphan*/ ,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (int /*<<< orphan*/ ,struct urb*) ; 

__attribute__((used)) static void
c67x00_giveback_urb(struct c67x00_hcd *c67x00, struct urb *urb, int status)
{
	struct c67x00_urb_priv *urbp;

	if (!urb)
		return;

	urbp = urb->hcpriv;
	urbp->status = status;

	list_del_init(&urbp->hep_node);

	c67x00_release_urb(c67x00, urb);
	usb_hcd_unlink_urb_from_ep(c67x00_hcd_to_hcd(c67x00), urb);
	spin_unlock(&c67x00->lock);
	usb_hcd_giveback_urb(c67x00_hcd_to_hcd(c67x00), urb, urbp->status);
	spin_lock(&c67x00->lock);
}