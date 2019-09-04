#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct shim_service {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  params ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/ * VCHI_SERVICE_HANDLE_T ;
typedef  int /*<<< orphan*/  VCHI_INSTANCE_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_9__ {int /*<<< orphan*/  version_min; int /*<<< orphan*/  version; struct shim_service* userdata; int /*<<< orphan*/  callback; int /*<<< orphan*/  fourcc; } ;
typedef  TYPE_2__ VCHIQ_SERVICE_PARAMS_T ;
typedef  int /*<<< orphan*/  VCHIQ_INSTANCE_T ;
struct TYPE_8__ {int /*<<< orphan*/  version_min; int /*<<< orphan*/  version; } ;
struct TYPE_10__ {TYPE_1__ version; int /*<<< orphan*/  service_id; } ;
typedef  TYPE_3__ SERVICE_CREATION_T ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct shim_service* service_alloc (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  service_free (struct shim_service*) ; 
 int /*<<< orphan*/  shim_callback ; 
 scalar_t__ vchiq_open_service (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

int32_t vchi_service_open(VCHI_INSTANCE_T instance_handle,
	SERVICE_CREATION_T *setup,
	VCHI_SERVICE_HANDLE_T *handle)
{
	VCHIQ_INSTANCE_T instance = (VCHIQ_INSTANCE_T)instance_handle;
	struct shim_service *service = service_alloc(instance, setup);

	*handle = (VCHI_SERVICE_HANDLE_T)service;

	if (service) {
		VCHIQ_SERVICE_PARAMS_T params;
		VCHIQ_STATUS_T status;

		memset(&params, 0, sizeof(params));
		params.fourcc = setup->service_id;
		params.callback = shim_callback;
		params.userdata = service;
		params.version = setup->version.version;
		params.version_min = setup->version.version_min;

		status = vchiq_open_service(instance, &params,
			&service->handle);
		if (status != VCHIQ_SUCCESS) {
			service_free(service);
			service = NULL;
			*handle = NULL;
		}
	}

	return (service != NULL) ? 0 : -1;
}