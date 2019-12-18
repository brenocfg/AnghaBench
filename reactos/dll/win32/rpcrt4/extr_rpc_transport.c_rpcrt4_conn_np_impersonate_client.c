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
struct TYPE_7__ {int /*<<< orphan*/  ctx; scalar_t__ AuthInfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  pipe; } ;
typedef  TYPE_1__ RpcConnection_np ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  ERROR_CANNOT_IMPERSONATE 128 
 int GetLastError () ; 
 int /*<<< orphan*/  ImpersonateNamedPipeClient (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCRT4_default_impersonate_client (TYPE_2__*) ; 
 int /*<<< orphan*/  RPC_S_NO_CONTEXT_AVAILABLE ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 scalar_t__ SecIsValidHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 

__attribute__((used)) static RPC_STATUS rpcrt4_conn_np_impersonate_client(RpcConnection *conn)
{
    RpcConnection_np *npc = (RpcConnection_np *)conn;
    BOOL ret;

    TRACE("(%p)\n", conn);

    if (conn->AuthInfo && SecIsValidHandle(&conn->ctx))
        return RPCRT4_default_impersonate_client(conn);

    ret = ImpersonateNamedPipeClient(npc->pipe);
    if (!ret)
    {
        DWORD error = GetLastError();
        WARN("ImpersonateNamedPipeClient failed with error %u\n", error);
        switch (error)
        {
        case ERROR_CANNOT_IMPERSONATE:
            return RPC_S_NO_CONTEXT_AVAILABLE;
        }
    }
    return RPC_S_OK;
}