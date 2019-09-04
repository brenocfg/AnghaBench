#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ obs_weak_service_t ;
struct TYPE_7__ {TYPE_1__* control; } ;
typedef  TYPE_2__ obs_service_t ;

/* Variables and functions */
 scalar_t__ obs_ref_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_service_destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_weak_service_release (TYPE_1__*) ; 

void obs_service_release(obs_service_t *service)
{
	if (!service)
		return;

	obs_weak_service_t *control = service->control;
	if (obs_ref_release(&control->ref)) {
		// The order of operations is important here since
		// get_context_by_name in obs.c relies on weak refs
		// being alive while the context is listed
		obs_service_destroy(service);
		obs_weak_service_release(control);
	}
}