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
struct pvc_device {scalar_t__ ether; scalar_t__ main; struct pvc_device* next; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_2__ {int dce_changed; scalar_t__ dce_pvc_count; struct pvc_device* first_pvc; } ;

/* Variables and functions */
 int /*<<< orphan*/ * dev_to_hdlc (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct pvc_device*) ; 
 TYPE_1__* state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (scalar_t__) ; 

__attribute__((used)) static void fr_destroy(struct net_device *frad)
{
	hdlc_device *hdlc = dev_to_hdlc(frad);
	struct pvc_device *pvc = state(hdlc)->first_pvc;
	state(hdlc)->first_pvc = NULL; /* All PVCs destroyed */
	state(hdlc)->dce_pvc_count = 0;
	state(hdlc)->dce_changed = 1;

	while (pvc) {
		struct pvc_device *next = pvc->next;
		/* destructors will free_netdev() main and ether */
		if (pvc->main)
			unregister_netdevice(pvc->main);

		if (pvc->ether)
			unregister_netdevice(pvc->ether);

		kfree(pvc);
		pvc = next;
	}
}