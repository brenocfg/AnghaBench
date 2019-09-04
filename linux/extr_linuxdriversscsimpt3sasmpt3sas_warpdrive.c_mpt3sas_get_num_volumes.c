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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct MPT3SAS_ADAPTER {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  IOCStatus; } ;
struct TYPE_5__ {int /*<<< orphan*/  DevHandle; } ;
typedef  TYPE_1__ Mpi2RaidVolPage1_t ;
typedef  TYPE_2__ Mpi2ConfigReply_t ;

/* Variables and functions */
 int MPI2_IOCSTATUS_CONFIG_INVALID_PAGE ; 
 int MPI2_IOCSTATUS_MASK ; 
 int /*<<< orphan*/  MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt3sas_config_get_raid_volume_pg1 (struct MPT3SAS_ADAPTER*,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

u8
mpt3sas_get_num_volumes(struct MPT3SAS_ADAPTER *ioc)
{
	Mpi2RaidVolPage1_t vol_pg1;
	Mpi2ConfigReply_t mpi_reply;
	u16 handle;
	u8 vol_cnt = 0;
	u16 ioc_status;

	handle = 0xFFFF;
	while (!(mpt3sas_config_get_raid_volume_pg1(ioc, &mpi_reply,
	    &vol_pg1, MPI2_RAID_VOLUME_PGAD_FORM_GET_NEXT_HANDLE, handle))) {
		ioc_status = le16_to_cpu(mpi_reply.IOCStatus) &
		    MPI2_IOCSTATUS_MASK;
		if (ioc_status == MPI2_IOCSTATUS_CONFIG_INVALID_PAGE)
			break;
		vol_cnt++;
		handle = le16_to_cpu(vol_pg1.DevHandle);
	}
	return vol_cnt;
}