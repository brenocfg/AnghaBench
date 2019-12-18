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
struct xen_9pfs_dataring {TYPE_1__* intf; } ;
struct TYPE_2__ {scalar_t__ out_cons; scalar_t__ out_prod; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 scalar_t__ XEN_9PFS_RING_SIZE ; 
 int /*<<< orphan*/  virt_mb () ; 
 scalar_t__ xen_9pfs_queued (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool p9_xen_write_todo(struct xen_9pfs_dataring *ring, RING_IDX size)
{
	RING_IDX cons, prod;

	cons = ring->intf->out_cons;
	prod = ring->intf->out_prod;
	virt_mb();

	return XEN_9PFS_RING_SIZE -
		xen_9pfs_queued(prod, cons, XEN_9PFS_RING_SIZE) >= size;
}