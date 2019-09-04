#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  num_adapters; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
struct hpi_response {int /*<<< orphan*/  error; TYPE_2__ u; } ;
struct hpi_message {int function; } ;
struct TYPE_7__ {int /*<<< orphan*/  gw_num_adapters; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_FUNC ; 
 int /*<<< orphan*/  HPI_OBJ_SUBSYSTEM ; 
#define  HPI_SUBSYS_CLOSE 134 
#define  HPI_SUBSYS_CREATE_ADAPTER 133 
#define  HPI_SUBSYS_DRIVER_LOAD 132 
#define  HPI_SUBSYS_DRIVER_UNLOAD 131 
#define  HPI_SUBSYS_GET_ADAPTER 130 
#define  HPI_SUBSYS_GET_NUM_ADAPTERS 129 
#define  HPI_SUBSYS_OPEN 128 
 TYPE_3__ adapters ; 
 int /*<<< orphan*/  hpi_init_response (struct hpi_response*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpios_alistlock_init (TYPE_3__*) ; 
 int /*<<< orphan*/  subsys_get_adapter (struct hpi_message*,struct hpi_response*) ; 
 int /*<<< orphan*/  wipe_adapter_list () ; 

__attribute__((used)) static void subsys_message(struct hpi_message *phm, struct hpi_response *phr)
{
	hpi_init_response(phr, HPI_OBJ_SUBSYSTEM, phm->function, 0);

	switch (phm->function) {
	case HPI_SUBSYS_OPEN:
	case HPI_SUBSYS_CLOSE:
	case HPI_SUBSYS_DRIVER_UNLOAD:
		break;
	case HPI_SUBSYS_DRIVER_LOAD:
		wipe_adapter_list();
		hpios_alistlock_init(&adapters);
		break;
	case HPI_SUBSYS_GET_ADAPTER:
		subsys_get_adapter(phm, phr);
		break;
	case HPI_SUBSYS_GET_NUM_ADAPTERS:
		phr->u.s.num_adapters = adapters.gw_num_adapters;
		break;
	case HPI_SUBSYS_CREATE_ADAPTER:
		break;
	default:
		phr->error = HPI_ERROR_INVALID_FUNC;
		break;
	}
}