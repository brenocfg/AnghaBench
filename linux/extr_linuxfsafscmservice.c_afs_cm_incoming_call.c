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
struct afs_call {int operation_ID; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
#define  CBCallBack 133 
#define  CBInitCallBackState 132 
#define  CBInitCallBackState3 131 
#define  CBProbe 130 
#define  CBProbeUuid 129 
#define  CBTellMeAboutYourself 128 
 int /*<<< orphan*/  _enter (char*,int) ; 
 int /*<<< orphan*/  afs_SRXCBCallBack ; 
 int /*<<< orphan*/  afs_SRXCBInitCallBackState ; 
 int /*<<< orphan*/  afs_SRXCBInitCallBackState3 ; 
 int /*<<< orphan*/  afs_SRXCBProbe ; 
 int /*<<< orphan*/  afs_SRXCBProbeUuid ; 
 int /*<<< orphan*/  afs_SRXCBTellMeAboutYourself ; 

bool afs_cm_incoming_call(struct afs_call *call)
{
	_enter("{CB.OP %u}", call->operation_ID);

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
	default:
		return false;
	}
}