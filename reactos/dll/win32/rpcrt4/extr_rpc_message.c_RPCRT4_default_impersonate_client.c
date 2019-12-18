#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  AuthInfo; } ;
typedef  int SECURITY_STATUS ;
typedef  TYPE_1__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int ImpersonateSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_S_CANNOT_SUPPORT ; 
 int /*<<< orphan*/  RPC_S_NO_CONTEXT_AVAILABLE ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_SEC_PKG_ERROR ; 
#define  SEC_E_NO_IMPERSONATION 130 
#define  SEC_E_OK 129 
#define  SEC_E_UNSUPPORTED_FUNCTION 128 
 int /*<<< orphan*/  SecIsValidHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*,int) ; 

RPC_STATUS RPCRT4_default_impersonate_client(RpcConnection *conn)
{
    SECURITY_STATUS sec_status;

    TRACE("(%p)\n", conn);

    if (!conn->AuthInfo || !SecIsValidHandle(&conn->ctx))
        return RPC_S_NO_CONTEXT_AVAILABLE;
    sec_status = ImpersonateSecurityContext(&conn->ctx);
    if (sec_status != SEC_E_OK)
        WARN("ImpersonateSecurityContext returned 0x%08x\n", sec_status);
    switch (sec_status)
    {
    case SEC_E_UNSUPPORTED_FUNCTION:
        return RPC_S_CANNOT_SUPPORT;
    case SEC_E_NO_IMPERSONATION:
        return RPC_S_NO_CONTEXT_AVAILABLE;
    case SEC_E_OK:
        return RPC_S_OK;
    default:
        return RPC_S_SEC_PKG_ERROR;
    }
}