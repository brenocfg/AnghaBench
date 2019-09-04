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
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ VCHI_INSTANCE_T ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  scalar_t__ VCHIQ_INSTANCE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_initialise (scalar_t__*) ; 
 int /*<<< orphan*/  vchiq_status_to_vchi (int /*<<< orphan*/ ) ; 

int32_t vchi_initialise(VCHI_INSTANCE_T *instance_handle)
{
	VCHIQ_INSTANCE_T instance;
	VCHIQ_STATUS_T status;

	status = vchiq_initialise(&instance);

	*instance_handle = (VCHI_INSTANCE_T)instance;

	return vchiq_status_to_vchi(status);
}