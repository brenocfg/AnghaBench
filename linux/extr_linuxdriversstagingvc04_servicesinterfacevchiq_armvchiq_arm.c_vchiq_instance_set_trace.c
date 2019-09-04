#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int trace; } ;
typedef  TYPE_1__ VCHIQ_SERVICE_T ;
typedef  TYPE_2__* VCHIQ_INSTANCE_T ;
struct TYPE_8__ {int trace; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 TYPE_1__* next_service_by_instance (int /*<<< orphan*/ ,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  unlock_service (TYPE_1__*) ; 

void
vchiq_instance_set_trace(VCHIQ_INSTANCE_T instance, int trace)
{
	VCHIQ_SERVICE_T *service;
	int i;

	i = 0;
	while ((service = next_service_by_instance(instance->state,
		instance, &i)) != NULL) {
		service->trace = trace;
		unlock_service(service);
	}
	instance->trace = (trace != 0);
}