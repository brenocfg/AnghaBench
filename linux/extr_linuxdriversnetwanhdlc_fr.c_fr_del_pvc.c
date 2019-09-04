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
struct pvc_device {int dummy; } ;
struct net_device {int flags; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_2__ {int dce_changed; int /*<<< orphan*/  dce_pvc_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int IFF_UP ; 
 int /*<<< orphan*/  delete_unused_pvcs (int /*<<< orphan*/ *) ; 
 struct pvc_device* find_pvc (int /*<<< orphan*/ *,unsigned int) ; 
 struct net_device** get_dev_p (struct pvc_device*,int) ; 
 int /*<<< orphan*/  pvc_is_used (struct pvc_device*) ; 
 TYPE_1__* state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int fr_del_pvc(hdlc_device *hdlc, unsigned int dlci, int type)
{
	struct pvc_device *pvc;
	struct net_device *dev;

	if ((pvc = find_pvc(hdlc, dlci)) == NULL)
		return -ENOENT;

	if ((dev = *get_dev_p(pvc, type)) == NULL)
		return -ENOENT;

	if (dev->flags & IFF_UP)
		return -EBUSY;		/* PVC in use */

	unregister_netdevice(dev); /* the destructor will free_netdev(dev) */
	*get_dev_p(pvc, type) = NULL;

	if (!pvc_is_used(pvc)) {
		state(hdlc)->dce_pvc_count--;
		state(hdlc)->dce_changed = 1;
	}
	delete_unused_pvcs(hdlc);
	return 0;
}