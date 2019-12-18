#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int destroy; int /*<<< orphan*/  active; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ obs_service_t ;

/* Variables and functions */
 int /*<<< orphan*/  actually_destroy_service (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_context_data_remove (int /*<<< orphan*/ *) ; 

void obs_service_destroy(obs_service_t *service)
{
	if (service) {
		obs_context_data_remove(&service->context);

		service->destroy = true;

		/* do NOT destroy the service until the service is no
		 * longer in use */
		if (!service->active)
			actually_destroy_service(service);
	}
}