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
struct usb_tt {struct ehci_tt** hcpriv; TYPE_1__* hub; scalar_t__ multi; } ;
struct usb_device {int ttport; int /*<<< orphan*/  bus; struct usb_tt* tt; } ;
struct ehci_tt {unsigned int tt_port; struct usb_tt* usb_tt; int /*<<< orphan*/  ps_list; int /*<<< orphan*/  tt_list; } ;
struct ehci_hcd {int /*<<< orphan*/  tt_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  maxchild; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct ehci_tt* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 struct ehci_hcd* hcd_to_ehci (int /*<<< orphan*/ ) ; 
 struct ehci_tt** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ehci_tt**) ; 
 struct ehci_tt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ehci_tt *find_tt(struct usb_device *udev)
{
	struct usb_tt		*utt = udev->tt;
	struct ehci_tt		*tt, **tt_index, **ptt;
	unsigned		port;
	bool			allocated_index = false;

	if (!utt)
		return NULL;		/* Not below a TT */

	/*
	 * Find/create our data structure.
	 * For hubs with a single TT, we get it directly.
	 * For hubs with multiple TTs, there's an extra level of pointers.
	 */
	tt_index = NULL;
	if (utt->multi) {
		tt_index = utt->hcpriv;
		if (!tt_index) {		/* Create the index array */
			tt_index = kcalloc(utt->hub->maxchild,
					   sizeof(*tt_index),
					   GFP_ATOMIC);
			if (!tt_index)
				return ERR_PTR(-ENOMEM);
			utt->hcpriv = tt_index;
			allocated_index = true;
		}
		port = udev->ttport - 1;
		ptt = &tt_index[port];
	} else {
		port = 0;
		ptt = (struct ehci_tt **) &utt->hcpriv;
	}

	tt = *ptt;
	if (!tt) {				/* Create the ehci_tt */
		struct ehci_hcd		*ehci =
				hcd_to_ehci(bus_to_hcd(udev->bus));

		tt = kzalloc(sizeof(*tt), GFP_ATOMIC);
		if (!tt) {
			if (allocated_index) {
				utt->hcpriv = NULL;
				kfree(tt_index);
			}
			return ERR_PTR(-ENOMEM);
		}
		list_add_tail(&tt->tt_list, &ehci->tt_list);
		INIT_LIST_HEAD(&tt->ps_list);
		tt->usb_tt = utt;
		tt->tt_port = port;
		*ptt = tt;
	}

	return tt;
}