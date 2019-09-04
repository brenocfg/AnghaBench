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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {scalar_t__ smid; int /*<<< orphan*/  done; int /*<<< orphan*/  status; int /*<<< orphan*/  reply; } ;
struct MPT3SAS_ADAPTER {TYPE_1__ tm_cmds; } ;
struct TYPE_6__ {int MsgLength; } ;
typedef  TYPE_2__ MPI2DefaultReply_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPT3_CMD_COMPLETE ; 
 int /*<<< orphan*/  MPT3_CMD_NOT_USED ; 
 int /*<<< orphan*/  MPT3_CMD_PENDING ; 
 int /*<<< orphan*/  MPT3_CMD_REPLY_VALID ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 TYPE_2__* mpt3sas_base_get_reply_virt_addr (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8
_scsih_tm_done(struct MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index, u32 reply)
{
	MPI2DefaultReply_t *mpi_reply;

	if (ioc->tm_cmds.status == MPT3_CMD_NOT_USED)
		return 1;
	if (ioc->tm_cmds.smid != smid)
		return 1;
	ioc->tm_cmds.status |= MPT3_CMD_COMPLETE;
	mpi_reply =  mpt3sas_base_get_reply_virt_addr(ioc, reply);
	if (mpi_reply) {
		memcpy(ioc->tm_cmds.reply, mpi_reply, mpi_reply->MsgLength*4);
		ioc->tm_cmds.status |= MPT3_CMD_REPLY_VALID;
	}
	ioc->tm_cmds.status &= ~MPT3_CMD_PENDING;
	complete(&ioc->tm_cmds.done);
	return 1;
}