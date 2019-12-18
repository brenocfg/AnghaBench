#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hpi_adapter_obj {size_t index; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__* adapter; int /*<<< orphan*/  gw_num_adapters; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ adapters ; 
 int /*<<< orphan*/  hpios_alistlock_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  hpios_alistlock_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void hpi_delete_adapter(struct hpi_adapter_obj *pao)
{
	if (!pao->type) {
		HPI_DEBUG_LOG(ERROR, "removing null adapter?\n");
		return;
	}

	hpios_alistlock_lock(&adapters);
	if (adapters.adapter[pao->index].type)
		adapters.gw_num_adapters--;
	memset(&adapters.adapter[pao->index], 0, sizeof(adapters.adapter[0]));
	hpios_alistlock_unlock(&adapters);
}