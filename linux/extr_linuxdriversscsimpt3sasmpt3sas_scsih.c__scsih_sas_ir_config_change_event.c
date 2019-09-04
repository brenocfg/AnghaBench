#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct fw_event_work {scalar_t__ event_data; } ;
struct MPT3SAS_ADAPTER {int logging_level; scalar_t__ hba_mpi_version_belonged; int /*<<< orphan*/  is_warpdrive; scalar_t__ shost_recovery; int /*<<< orphan*/  hide_ir_msg; } ;
struct TYPE_10__ {int NumElements; int /*<<< orphan*/ * ConfigElement; int /*<<< orphan*/  Flags; } ;
struct TYPE_9__ {int ReasonCode; int /*<<< orphan*/  VolDevHandle; int /*<<< orphan*/  PhysDiskNum; int /*<<< orphan*/  PhysDiskDevHandle; } ;
typedef  TYPE_1__ Mpi2EventIrConfigElement_t ;
typedef  TYPE_2__ Mpi2EventDataIrConfigChangeList_t ;

/* Variables and functions */
 int MPI2_EVENT_IR_CHANGE_FLAGS_FOREIGN_CONFIG ; 
#define  MPI2_EVENT_IR_CHANGE_RC_ADDED 135 
#define  MPI2_EVENT_IR_CHANGE_RC_HIDE 134 
#define  MPI2_EVENT_IR_CHANGE_RC_PD_CREATED 133 
#define  MPI2_EVENT_IR_CHANGE_RC_PD_DELETED 132 
#define  MPI2_EVENT_IR_CHANGE_RC_REMOVED 131 
#define  MPI2_EVENT_IR_CHANGE_RC_UNHIDE 130 
#define  MPI2_EVENT_IR_CHANGE_RC_VOLUME_CREATED 129 
#define  MPI2_EVENT_IR_CHANGE_RC_VOLUME_DELETED 128 
 scalar_t__ MPI2_VERSION ; 
 int MPT_DEBUG_EVENT_WORK_TASK ; 
 int /*<<< orphan*/  _scsih_ir_fastpath (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _scsih_sas_ir_config_change_event_debug (struct MPT3SAS_ADAPTER*,TYPE_2__*) ; 
 int /*<<< orphan*/  _scsih_sas_pd_add (struct MPT3SAS_ADAPTER*,TYPE_1__*) ; 
 int /*<<< orphan*/  _scsih_sas_pd_delete (struct MPT3SAS_ADAPTER*,TYPE_1__*) ; 
 int /*<<< orphan*/  _scsih_sas_pd_expose (struct MPT3SAS_ADAPTER*,TYPE_1__*) ; 
 int /*<<< orphan*/  _scsih_sas_pd_hide (struct MPT3SAS_ADAPTER*,TYPE_1__*) ; 
 int /*<<< orphan*/  _scsih_sas_volume_add (struct MPT3SAS_ADAPTER*,TYPE_1__*) ; 
 int /*<<< orphan*/  _scsih_sas_volume_delete (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_sas_ir_config_change_event(struct MPT3SAS_ADAPTER *ioc,
	struct fw_event_work *fw_event)
{
	Mpi2EventIrConfigElement_t *element;
	int i;
	u8 foreign_config;
	Mpi2EventDataIrConfigChangeList_t *event_data =
		(Mpi2EventDataIrConfigChangeList_t *)
		fw_event->event_data;

	if ((ioc->logging_level & MPT_DEBUG_EVENT_WORK_TASK) &&
	     (!ioc->hide_ir_msg))
		_scsih_sas_ir_config_change_event_debug(ioc, event_data);

	foreign_config = (le32_to_cpu(event_data->Flags) &
	    MPI2_EVENT_IR_CHANGE_FLAGS_FOREIGN_CONFIG) ? 1 : 0;

	element = (Mpi2EventIrConfigElement_t *)&event_data->ConfigElement[0];
	if (ioc->shost_recovery &&
	    ioc->hba_mpi_version_belonged != MPI2_VERSION) {
		for (i = 0; i < event_data->NumElements; i++, element++) {
			if (element->ReasonCode == MPI2_EVENT_IR_CHANGE_RC_HIDE)
				_scsih_ir_fastpath(ioc,
					le16_to_cpu(element->PhysDiskDevHandle),
					element->PhysDiskNum);
		}
		return;
	}

	for (i = 0; i < event_data->NumElements; i++, element++) {

		switch (element->ReasonCode) {
		case MPI2_EVENT_IR_CHANGE_RC_VOLUME_CREATED:
		case MPI2_EVENT_IR_CHANGE_RC_ADDED:
			if (!foreign_config)
				_scsih_sas_volume_add(ioc, element);
			break;
		case MPI2_EVENT_IR_CHANGE_RC_VOLUME_DELETED:
		case MPI2_EVENT_IR_CHANGE_RC_REMOVED:
			if (!foreign_config)
				_scsih_sas_volume_delete(ioc,
				    le16_to_cpu(element->VolDevHandle));
			break;
		case MPI2_EVENT_IR_CHANGE_RC_PD_CREATED:
			if (!ioc->is_warpdrive)
				_scsih_sas_pd_hide(ioc, element);
			break;
		case MPI2_EVENT_IR_CHANGE_RC_PD_DELETED:
			if (!ioc->is_warpdrive)
				_scsih_sas_pd_expose(ioc, element);
			break;
		case MPI2_EVENT_IR_CHANGE_RC_HIDE:
			if (!ioc->is_warpdrive)
				_scsih_sas_pd_add(ioc, element);
			break;
		case MPI2_EVENT_IR_CHANGE_RC_UNHIDE:
			if (!ioc->is_warpdrive)
				_scsih_sas_pd_delete(ioc, element);
			break;
		}
	}
}