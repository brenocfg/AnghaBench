#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_3__ {scalar_t__ ReasonCode; int /*<<< orphan*/  VolDevHandle; int /*<<< orphan*/  NewValue; } ;
typedef  TYPE_1__ Mpi2EventDataIrVolume_t ;

/* Variables and functions */
 scalar_t__ MPI2_EVENT_IR_VOLUME_RC_STATE_CHANGED ; 
 scalar_t__ MPI2_RAID_VOL_STATE_FAILED ; 
 scalar_t__ MPI2_RAID_VOL_STATE_MISSING ; 
 int /*<<< orphan*/  _scsih_set_volume_delete_flag (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_scsih_check_volume_delete_events(struct MPT3SAS_ADAPTER *ioc,
	Mpi2EventDataIrVolume_t *event_data)
{
	u32 state;

	if (event_data->ReasonCode != MPI2_EVENT_IR_VOLUME_RC_STATE_CHANGED)
		return;
	state = le32_to_cpu(event_data->NewValue);
	if (state == MPI2_RAID_VOL_STATE_MISSING || state ==
	    MPI2_RAID_VOL_STATE_FAILED)
		_scsih_set_volume_delete_flag(ioc,
		    le16_to_cpu(event_data->VolDevHandle));
}