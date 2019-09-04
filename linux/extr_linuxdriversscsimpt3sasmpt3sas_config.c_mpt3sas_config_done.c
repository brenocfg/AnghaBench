#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_6__ {scalar_t__ smid; int /*<<< orphan*/  done; int /*<<< orphan*/  status; int /*<<< orphan*/  reply; } ;
struct MPT3SAS_ADAPTER {TYPE_1__ config_cmds; } ;
struct TYPE_7__ {int MsgLength; } ;
typedef  TYPE_2__ MPI2DefaultReply_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPT3_CMD_COMPLETE ; 
 int /*<<< orphan*/  MPT3_CMD_NOT_USED ; 
 int /*<<< orphan*/  MPT3_CMD_PENDING ; 
 int /*<<< orphan*/  MPT3_CMD_REPLY_VALID ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  _config_display_some_debug (struct MPT3SAS_ADAPTER*,scalar_t__,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 TYPE_2__* mpt3sas_base_get_reply_virt_addr (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 

u8
mpt3sas_config_done(struct MPT3SAS_ADAPTER *ioc, u16 smid, u8 msix_index,
	u32 reply)
{
	MPI2DefaultReply_t *mpi_reply;

	if (ioc->config_cmds.status == MPT3_CMD_NOT_USED)
		return 1;
	if (ioc->config_cmds.smid != smid)
		return 1;
	ioc->config_cmds.status |= MPT3_CMD_COMPLETE;
	mpi_reply =  mpt3sas_base_get_reply_virt_addr(ioc, reply);
	if (mpi_reply) {
		ioc->config_cmds.status |= MPT3_CMD_REPLY_VALID;
		memcpy(ioc->config_cmds.reply, mpi_reply,
		    mpi_reply->MsgLength*4);
	}
	ioc->config_cmds.status &= ~MPT3_CMD_PENDING;
	_config_display_some_debug(ioc, smid, "config_done", mpi_reply);
	ioc->config_cmds.smid = USHRT_MAX;
	complete(&ioc->config_cmds.done);
	return 1;
}