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
struct afs_call {int operation_ID; int /*<<< orphan*/ * type; int /*<<< orphan*/  service_id; int /*<<< orphan*/  rxcall; TYPE_1__* net; int /*<<< orphan*/  epoch; } ;
struct TYPE_2__ {int /*<<< orphan*/  socket; } ;

/* Variables and functions */
#define  CBCallBack 134 
#define  CBInitCallBackState 133 
#define  CBInitCallBackState3 132 
#define  CBProbe 131 
#define  CBProbeUuid 130 
#define  CBTellMeAboutYourself 129 
#define  YFSCBCallBack 128 
 int /*<<< orphan*/  YFS_CM_SERVICE ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  afs_SRXCBCallBack ; 
 int /*<<< orphan*/  afs_SRXCBInitCallBackState ; 
 int /*<<< orphan*/  afs_SRXCBInitCallBackState3 ; 
 int /*<<< orphan*/  afs_SRXCBProbe ; 
 int /*<<< orphan*/  afs_SRXCBProbeUuid ; 
 int /*<<< orphan*/  afs_SRXCBTellMeAboutYourself ; 
 int /*<<< orphan*/  afs_SRXYFSCB_CallBack ; 
 int /*<<< orphan*/  rxrpc_kernel_get_epoch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool afs_cm_incoming_call(struct afs_call *call)
{
	_enter("{%u, CB.OP %u}", call->service_id, call->operation_ID);

	call->epoch = rxrpc_kernel_get_epoch(call->net->socket, call->rxcall);

	switch (call->operation_ID) {
	case CBCallBack:
		call->type = &afs_SRXCBCallBack;
		return true;
	case CBInitCallBackState:
		call->type = &afs_SRXCBInitCallBackState;
		return true;
	case CBInitCallBackState3:
		call->type = &afs_SRXCBInitCallBackState3;
		return true;
	case CBProbe:
		call->type = &afs_SRXCBProbe;
		return true;
	case CBProbeUuid:
		call->type = &afs_SRXCBProbeUuid;
		return true;
	case CBTellMeAboutYourself:
		call->type = &afs_SRXCBTellMeAboutYourself;
		return true;
	case YFSCBCallBack:
		if (call->service_id != YFS_CM_SERVICE)
			return false;
		call->type = &afs_SRXYFSCB_CallBack;
		return true;
	default:
		return false;
	}
}