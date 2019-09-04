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
struct pvc_device {struct pvc_device* next; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_2__ {struct pvc_device* first_pvc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pvc_device*) ; 
 int /*<<< orphan*/  pvc_is_used (struct pvc_device*) ; 
 TYPE_1__* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void delete_unused_pvcs(hdlc_device *hdlc)
{
	struct pvc_device **pvc_p = &state(hdlc)->first_pvc;

	while (*pvc_p) {
		if (!pvc_is_used(*pvc_p)) {
			struct pvc_device *pvc = *pvc_p;
#ifdef DEBUG_PVC
			printk(KERN_DEBUG "freeing unused pvc: %p\n", pvc);
#endif
			*pvc_p = pvc->next;
			kfree(pvc);
			continue;
		}
		pvc_p = &(*pvc_p)->next;
	}
}