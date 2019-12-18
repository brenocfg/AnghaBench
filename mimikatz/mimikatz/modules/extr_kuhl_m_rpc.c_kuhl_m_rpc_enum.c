#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ UUID ;
struct TYPE_8__ {TYPE_1__ Uuid; } ;
typedef  scalar_t__ RPC_WSTR ;
typedef  scalar_t__ RPC_STATUS ;
typedef  TYPE_2__ RPC_IF_ID ;
typedef  int /*<<< orphan*/  RPC_EP_INQ_HANDLE ;
typedef  scalar_t__ RPC_BINDING_HANDLE ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * KULL_M_RPC_AUTH_IDENTITY_HANDLE_NULLSESSION ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  RPC_C_AUTHN_GSS_NEGOTIATE ; 
 int /*<<< orphan*/  RPC_C_EP_ALL_ELTS ; 
 int /*<<< orphan*/  RPC_C_IMP_LEVEL_DEFAULT ; 
 scalar_t__ RPC_S_OK ; 
 scalar_t__ RPC_X_NO_MORE_ENTRIES ; 
 int /*<<< orphan*/  RpcBindingFree (scalar_t__*) ; 
 scalar_t__ RpcBindingToStringBinding (scalar_t__,scalar_t__*) ; 
 scalar_t__ RpcMgmtEpEltInqBegin (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RpcMgmtEpEltInqDone (int /*<<< orphan*/ *) ; 
 scalar_t__ RpcMgmtEpEltInqNext (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  RpcStringFree (scalar_t__*) ; 
 scalar_t__ RtlEqualGuid (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kull_m_rpc_createBinding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_rpc_deleteBinding (scalar_t__*) ; 
 int /*<<< orphan*/  kull_m_rpc_getArgs (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (TYPE_1__*) ; 

NTSTATUS kuhl_m_rpc_enum(int argc, wchar_t * argv[])
{
	RPC_STATUS status, enumStatus;
	RPC_BINDING_HANDLE Binding, EnumBinding;
	RPC_EP_INQ_HANDLE InquiryContext;
	RPC_IF_ID IfId;
	RPC_WSTR Annotation, bindString;
	UUID prev = {0};
	BOOL isNullSession, sameId, avoidMsBugWasHere = FALSE;
	PCWSTR szRemote, szProtSeq;
	DWORD AuthnSvc;
	
	kull_m_rpc_getArgs(argc, argv, &szRemote, &szProtSeq, NULL, NULL, &AuthnSvc, RPC_C_AUTHN_GSS_NEGOTIATE, &isNullSession, NULL, TRUE);
	if(kull_m_rpc_createBinding(NULL, szProtSeq, szRemote, NULL, NULL, FALSE, AuthnSvc, isNullSession ? KULL_M_RPC_AUTH_IDENTITY_HANDLE_NULLSESSION : NULL, RPC_C_IMP_LEVEL_DEFAULT, &Binding, NULL))
	{
		status = RpcMgmtEpEltInqBegin(Binding, RPC_C_EP_ALL_ELTS, NULL, 0, NULL, &InquiryContext);
		if(status == RPC_S_OK)
		{
			do
			{
				enumStatus = RpcMgmtEpEltInqNext(InquiryContext, &IfId, &EnumBinding, NULL, &Annotation);
				if(enumStatus == RPC_S_OK)
				{
					avoidMsBugWasHere = TRUE;
					sameId = RtlEqualGuid(&IfId.Uuid, &prev);
					if(!sameId)
					{
						kprintf(L"UUID: ");
						kull_m_string_displayGUID(&IfId.Uuid);
						if(Annotation)
						{
							kprintf(L"\t%s", Annotation);
							RpcStringFree(&Annotation);
						}
						kprintf(L"\n");
						prev = IfId.Uuid;
					}
					if(EnumBinding)
					{
						status = RpcBindingToStringBinding(EnumBinding, &bindString);
						if(status == RPC_S_OK)
						{
							kprintf(L"\t%s\n", bindString);
							RpcStringFree(&bindString);
						}
						else PRINT_ERROR(L"RpcBindingToStringBinding: %08x\n", status);
						RpcBindingFree(&EnumBinding);
					}
				}
			} while(enumStatus == RPC_S_OK);

			if(!avoidMsBugWasHere && (enumStatus == RPC_X_NO_MORE_ENTRIES))
				PRINT_ERROR(L"RpcMgmtEpEltInqNext: %08x, maybe really no EP, maybe network problem\n", enumStatus);
			else if(enumStatus != RPC_X_NO_MORE_ENTRIES)
				PRINT_ERROR(L"RpcMgmtEpEltInqNext: %08x\n", enumStatus);
			status = RpcMgmtEpEltInqDone(&InquiryContext);
			if(status != RPC_S_OK)
				PRINT_ERROR(L"RpcMgmtEpEltInqDone: %08x\n", status);
		}
		else PRINT_ERROR(L"RpcMgmtEpEltInqBegin: %08x\n", status);
		kull_m_rpc_deleteBinding(&Binding);
	}
	return STATUS_SUCCESS;
}