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
struct pvcalls_data_intf {scalar_t__ in_error; int /*<<< orphan*/  in_prod; int /*<<< orphan*/  in_cons; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  PVCALLS_RING_ORDER ; 
 int /*<<< orphan*/  XEN_FLEX_RING_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ pvcalls_queued (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pvcalls_front_read_todo(struct sock_mapping *map)
{
	struct pvcalls_data_intf *intf = map->active.ring;
	RING_IDX cons, prod;
	int32_t error;

	cons = intf->in_cons;
	prod = intf->in_prod;
	error = intf->in_error;
	return (error != 0 ||
		pvcalls_queued(prod, cons,
			       XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER)) != 0);
}