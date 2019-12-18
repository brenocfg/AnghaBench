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
typedef  int /*<<< orphan*/  u16 ;
struct hpi_adapter_obj {int index; scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  gw_num_adapters; struct hpi_adapter_obj* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  HPI_ERROR_BAD_ADAPTER_NUMBER ; 
 int /*<<< orphan*/  HPI_ERROR_DUPLICATE_ADAPTER_NUMBER ; 
 int HPI_MAX_ADAPTERS ; 
 int /*<<< orphan*/  WARNING ; 
 TYPE_1__ adapters ; 
 int /*<<< orphan*/  hpios_alistlock_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  hpios_alistlock_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  hpios_dsplock_init (struct hpi_adapter_obj*) ; 

u16 hpi_add_adapter(struct hpi_adapter_obj *pao)
{
	u16 retval = 0;
	/*HPI_ASSERT(pao->type); */

	hpios_alistlock_lock(&adapters);

	if (pao->index >= HPI_MAX_ADAPTERS) {
		retval = HPI_ERROR_BAD_ADAPTER_NUMBER;
		goto unlock;
	}

	if (adapters.adapter[pao->index].type) {
		int a;
		for (a = HPI_MAX_ADAPTERS - 1; a >= 0; a--) {
			if (!adapters.adapter[a].type) {
				HPI_DEBUG_LOG(WARNING,
					"ASI%X duplicate index %d moved to %d\n",
					pao->type, pao->index, a);
				pao->index = a;
				break;
			}
		}
		if (a < 0) {
			retval = HPI_ERROR_DUPLICATE_ADAPTER_NUMBER;
			goto unlock;
		}
	}
	adapters.adapter[pao->index] = *pao;
	hpios_dsplock_init(&adapters.adapter[pao->index]);
	adapters.gw_num_adapters++;

unlock:
	hpios_alistlock_unlock(&adapters);
	return retval;
}