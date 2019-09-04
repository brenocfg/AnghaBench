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
struct urb_priv {int /*<<< orphan*/  td_list; int /*<<< orphan*/  node; struct urb* urb; } ;
struct urb {struct urb_priv* hcpriv; } ;
struct uhci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct urb_priv* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_up_cachep ; 

__attribute__((used)) static inline struct urb_priv *uhci_alloc_urb_priv(struct uhci_hcd *uhci,
		struct urb *urb)
{
	struct urb_priv *urbp;

	urbp = kmem_cache_zalloc(uhci_up_cachep, GFP_ATOMIC);
	if (!urbp)
		return NULL;

	urbp->urb = urb;
	urb->hcpriv = urbp;

	INIT_LIST_HEAD(&urbp->node);
	INIT_LIST_HEAD(&urbp->td_list);

	return urbp;
}