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
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  RPC_BINDING_VECTOR ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR (char*,scalar_t__) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  RpcBindingVectorFree (int /*<<< orphan*/ **) ; 
 scalar_t__ RpcEpUnregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RpcMgmtStopServerListening (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcMgmtWaitServerListen () ; 
 scalar_t__ RpcServerInqBindings (int /*<<< orphan*/ **) ; 
 scalar_t__ RpcServerUnregisterIfEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drsuapi_v4_0_s_ifspec ; 
 int /*<<< orphan*/  kprintf (char*) ; 

NTSTATUS kull_m_rpc_drsr_stop_server()
{
	RPC_STATUS status;
	RPC_BINDING_VECTOR *vector = NULL;

	status = RpcServerInqBindings(&vector);
	if(status == RPC_S_OK)
	{
		status = RpcEpUnregister(drsuapi_v4_0_s_ifspec, vector, NULL);
		if(status == RPC_S_OK)
			kprintf(L" > RPC bind unregistered\n");
		else PRINT_ERROR(L"RpcEpUnregister: %08x\n", status);
		RpcBindingVectorFree(&vector);
	}
	else PRINT_ERROR(L"RpcServerInqBindings: %08x\n", status);
	status = RpcServerUnregisterIfEx(drsuapi_v4_0_s_ifspec, NULL, 1);
	if(status != RPC_S_OK)
		PRINT_ERROR(L"RpcServerUnregisterIf: %08x\n", status);
	status = RpcMgmtStopServerListening(NULL);
	if(status != RPC_S_OK)
		PRINT_ERROR(L"RpcMgmtStopServerListening: %08x\n", status);
	else
	{
		kprintf(L" > stopping RPC server\n");
		RpcMgmtWaitServerListen();
		kprintf(L" > RPC server stopped\n");
	}
	return status;
}