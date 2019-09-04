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
typedef  int u16 ;
struct fw_event_work {int /*<<< orphan*/  event_data; struct MPT3SAS_ADAPTER* ioc; int /*<<< orphan*/  event; } ;
struct SL_WH_TRIGGERS_EVENT_DATA_T {int dummy; } ;
struct MPT3SAS_ADAPTER {scalar_t__ is_driver_loading; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPT3SAS_PROCESS_TRIGGER_DIAG ; 
 int /*<<< orphan*/  _scsih_fw_event_add (struct MPT3SAS_ADAPTER*,struct fw_event_work*) ; 
 struct fw_event_work* alloc_fw_event_work (int) ; 
 int /*<<< orphan*/  fw_event_work_put (struct fw_event_work*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct SL_WH_TRIGGERS_EVENT_DATA_T*,int) ; 

void
mpt3sas_send_trigger_data_event(struct MPT3SAS_ADAPTER *ioc,
	struct SL_WH_TRIGGERS_EVENT_DATA_T *event_data)
{
	struct fw_event_work *fw_event;
	u16 sz;

	if (ioc->is_driver_loading)
		return;
	sz = sizeof(*event_data);
	fw_event = alloc_fw_event_work(sz);
	if (!fw_event)
		return;
	fw_event->event = MPT3SAS_PROCESS_TRIGGER_DIAG;
	fw_event->ioc = ioc;
	memcpy(fw_event->event_data, event_data, sizeof(*event_data));
	_scsih_fw_event_add(ioc, fw_event);
	fw_event_work_put(fw_event);
}