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
typedef  scalar_t__ u16 ;
struct pvc_device {scalar_t__ dlci; struct pvc_device* next; struct net_device* frad; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_2__ {struct pvc_device* first_pvc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 struct pvc_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pvc_device *add_pvc(struct net_device *dev, u16 dlci)
{
	hdlc_device *hdlc = dev_to_hdlc(dev);
	struct pvc_device *pvc, **pvc_p = &state(hdlc)->first_pvc;

	while (*pvc_p) {
		if ((*pvc_p)->dlci == dlci)
			return *pvc_p;
		if ((*pvc_p)->dlci > dlci)
			break;	/* the list is sorted */
		pvc_p = &(*pvc_p)->next;
	}

	pvc = kzalloc(sizeof(*pvc), GFP_ATOMIC);
#ifdef DEBUG_PVC
	printk(KERN_DEBUG "add_pvc: allocated pvc %p, frad %p\n", pvc, dev);
#endif
	if (!pvc)
		return NULL;

	pvc->dlci = dlci;
	pvc->frad = dev;
	pvc->next = *pvc_p;	/* Put it in the chain */
	*pvc_p = pvc;
	return pvc;
}