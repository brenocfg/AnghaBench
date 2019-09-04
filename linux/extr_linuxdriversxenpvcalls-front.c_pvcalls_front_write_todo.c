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
struct TYPE_2__ {struct pvcalls_data_intf* ring; } ;
struct sock_mapping {TYPE_1__ active; } ;
struct pvcalls_data_intf {scalar_t__ out_prod; scalar_t__ out_cons; int /*<<< orphan*/  out_error; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTCONN ; 
 int /*<<< orphan*/  PVCALLS_RING_ORDER ; 
 scalar_t__ XEN_FLEX_RING_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ pvcalls_queued (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool pvcalls_front_write_todo(struct sock_mapping *map)
{
	struct pvcalls_data_intf *intf = map->active.ring;
	RING_IDX cons, prod, size = XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER);
	int32_t error;

	error = intf->out_error;
	if (error == -ENOTCONN)
		return false;
	if (error != 0)
		return true;

	cons = intf->out_cons;
	prod = intf->out_prod;
	return !!(size - pvcalls_queued(prod, cons, size));
}