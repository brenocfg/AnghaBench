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
struct vnet_port {int q_index; struct vnet* vp; } ;
struct vnet {scalar_t__* q_used; int /*<<< orphan*/  nports; } ;

/* Variables and functions */
 int VNET_MAX_TXQS ; 

void sunvnet_port_add_txq_common(struct vnet_port *port)
{
	struct vnet *vp = port->vp;
	int smallest = 0;
	int i;

	/* find the first least-used q
	 * When there are more ldoms than q's, we start to
	 * double up on ports per queue.
	 */
	for (i = 0; i < VNET_MAX_TXQS; i++) {
		if (vp->q_used[i] == 0) {
			smallest = i;
			break;
		}
		if (vp->q_used[i] < vp->q_used[smallest])
			smallest = i;
	}

	vp->nports++;
	vp->q_used[smallest]++;
	port->q_index = smallest;
}