#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ctx; scalar_t__ AuthInfo; } ;
typedef  TYPE_1__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  RPCRT4_default_revert_to_self (TYPE_1__*) ; 
 int /*<<< orphan*/  RPC_S_NO_CONTEXT_AVAILABLE ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RevertToSelf () ; 
 scalar_t__ SecIsValidHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RPC_STATUS rpcrt4_conn_np_revert_to_self(RpcConnection *conn)
{
    BOOL ret;

    TRACE("(%p)\n", conn);

    if (conn->AuthInfo && SecIsValidHandle(&conn->ctx))
        return RPCRT4_default_revert_to_self(conn);

    ret = RevertToSelf();
    if (!ret)
    {
        WARN("RevertToSelf failed with error %u\n", GetLastError());
        return RPC_S_NO_CONTEXT_AVAILABLE;
    }
    return RPC_S_OK;
}