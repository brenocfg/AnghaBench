#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_11__ {int /*<<< orphan*/  adapter_index; int /*<<< orphan*/  adapter_type; int /*<<< orphan*/  data; } ;
struct TYPE_12__ {TYPE_5__ s; } ;
struct hpi_response {scalar_t__ error; TYPE_6__ u; scalar_t__ specific_error; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pci; } ;
struct TYPE_8__ {TYPE_1__ r; } ;
struct TYPE_9__ {TYPE_2__ resource; } ;
struct TYPE_10__ {TYPE_3__ s; } ;
struct hpi_message {TYPE_4__ u; } ;
struct hpi_hw_obj {int dummy; } ;
struct hpi_adapter_obj {int /*<<< orphan*/  index; int /*<<< orphan*/  type; int /*<<< orphan*/  pci; int /*<<< orphan*/  priv; } ;
typedef  int /*<<< orphan*/  ao ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ HPI_ERROR_BACKEND_BASE ; 
 scalar_t__ HPI_ERROR_DSP_BOOTLOAD ; 
 scalar_t__ HPI_ERROR_MEMORY_ALLOC ; 
 scalar_t__ create_adapter_obj (struct hpi_adapter_obj*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_adapter_obj (struct hpi_adapter_obj*) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hpi_adapter_obj*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void subsys_create_adapter(struct hpi_message *phm,
	struct hpi_response *phr)
{
	/* create temp adapter obj, because we don't know what index yet */
	struct hpi_adapter_obj ao;
	u32 os_error_code;
	u16 err;

	HPI_DEBUG_LOG(DEBUG, " subsys_create_adapter\n");

	memset(&ao, 0, sizeof(ao));

	ao.priv = kzalloc(sizeof(struct hpi_hw_obj), GFP_KERNEL);
	if (!ao.priv) {
		HPI_DEBUG_LOG(ERROR, "can't get mem for adapter object\n");
		phr->error = HPI_ERROR_MEMORY_ALLOC;
		return;
	}

	ao.pci = *phm->u.s.resource.r.pci;
	err = create_adapter_obj(&ao, &os_error_code);
	if (err) {
		delete_adapter_obj(&ao);
		if (err >= HPI_ERROR_BACKEND_BASE) {
			phr->error = HPI_ERROR_DSP_BOOTLOAD;
			phr->specific_error = err;
		} else {
			phr->error = err;
		}
		phr->u.s.data = os_error_code;
		return;
	}

	phr->u.s.adapter_type = ao.type;
	phr->u.s.adapter_index = ao.index;
	phr->error = 0;
}