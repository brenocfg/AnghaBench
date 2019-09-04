#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct hpi_adapter_obj {scalar_t__ type; } ;
struct TYPE_2__ {struct hpi_adapter_obj* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_DEBUG_LOG (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t HPI_MAX_ADAPTERS ; 
 int /*<<< orphan*/  VERBOSE ; 
 TYPE_1__ adapters ; 

struct hpi_adapter_obj *hpi_find_adapter(u16 adapter_index)
{
	struct hpi_adapter_obj *pao = NULL;

	if (adapter_index >= HPI_MAX_ADAPTERS) {
		HPI_DEBUG_LOG(VERBOSE, "find_adapter invalid index %d\n",
			adapter_index);
		return NULL;
	}

	pao = &adapters.adapter[adapter_index];
	if (pao->type != 0) {
		/*
		   HPI_DEBUG_LOG(VERBOSE, "Found adapter index %d\n",
		   wAdapterIndex);
		 */
		return pao;
	} else {
		/*
		   HPI_DEBUG_LOG(VERBOSE, "No adapter index %d\n",
		   wAdapterIndex);
		 */
		return NULL;
	}
}