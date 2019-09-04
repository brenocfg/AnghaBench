#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_6__ {scalar_t__ adapter_type; int /*<<< orphan*/  adapter_index; } ;
struct TYPE_7__ {TYPE_2__ s; } ;
struct hpi_response {int /*<<< orphan*/  error; TYPE_3__ u; } ;
struct hpi_message {int obj_index; } ;
struct TYPE_8__ {TYPE_1__* adapter; } ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ERROR_INVALID_OBJ_INDEX ; 
 size_t HPI_MAX_ADAPTERS ; 
 TYPE_4__ adapters ; 

__attribute__((used)) static void subsys_get_adapter(struct hpi_message *phm,
	struct hpi_response *phr)
{
	int count = phm->obj_index;
	u16 index = 0;

	/* find the nCount'th nonzero adapter in array */
	for (index = 0; index < HPI_MAX_ADAPTERS; index++) {
		if (adapters.adapter[index].type) {
			if (!count)
				break;
			count--;
		}
	}

	if (index < HPI_MAX_ADAPTERS) {
		phr->u.s.adapter_index = adapters.adapter[index].index;
		phr->u.s.adapter_type = adapters.adapter[index].type;
	} else {
		phr->u.s.adapter_index = 0;
		phr->u.s.adapter_type = 0;
		phr->error = HPI_ERROR_INVALID_OBJ_INDEX;
	}
}