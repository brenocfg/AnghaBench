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
struct TYPE_8__ {scalar_t__ wait_release; scalar_t__ assoc; scalar_t__ server_binding; scalar_t__ QOS; scalar_t__ AuthInfo; struct TYPE_8__* CookieAuth; struct TYPE_8__* NetworkOptions; int /*<<< orphan*/  NetworkAddr; int /*<<< orphan*/  Endpoint; int /*<<< orphan*/  ref; TYPE_1__* protseq; int /*<<< orphan*/  protseq_entry; } ;
struct TYPE_7__ {int /*<<< orphan*/  cs; } ;
typedef  TYPE_2__ RpcConnection ;
typedef  scalar_t__ LONG ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPCRT4_CloseConnection (TYPE_2__*) ; 
 int /*<<< orphan*/  RPCRT4_ReleaseBinding (scalar_t__) ; 
 int /*<<< orphan*/  RPCRT4_strfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RpcAssoc_ConnectionReleased (scalar_t__) ; 
 int /*<<< orphan*/  RpcAuthInfo_Release (scalar_t__) ; 
 int /*<<< orphan*/  RpcQualityOfService_Release (scalar_t__) ; 
 int /*<<< orphan*/  SetEvent (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

void RPCRT4_ReleaseConnection(RpcConnection *connection)
{
    LONG ref;

    /* protseq stores a list of active connections, but does not own references to them.
     * It may need to grab a connection from the list, which could lead to a race if
     * connection is being released, but not yet removed from the list. We handle that
     * by synchronizing on CS here. */
    if (connection->protseq)
    {
        EnterCriticalSection(&connection->protseq->cs);
        ref = InterlockedDecrement(&connection->ref);
        if (!ref)
            list_remove(&connection->protseq_entry);
        LeaveCriticalSection(&connection->protseq->cs);
    }
    else
    {
        ref = InterlockedDecrement(&connection->ref);
    }

    TRACE("%p ref=%u\n", connection, ref);

    if (!ref)
    {
        RPCRT4_CloseConnection(connection);
        RPCRT4_strfree(connection->Endpoint);
        RPCRT4_strfree(connection->NetworkAddr);
        HeapFree(GetProcessHeap(), 0, connection->NetworkOptions);
        HeapFree(GetProcessHeap(), 0, connection->CookieAuth);
        if (connection->AuthInfo) RpcAuthInfo_Release(connection->AuthInfo);
        if (connection->QOS) RpcQualityOfService_Release(connection->QOS);

        /* server-only */
        if (connection->server_binding) RPCRT4_ReleaseBinding(connection->server_binding);
        else if (connection->assoc) RpcAssoc_ConnectionReleased(connection->assoc);

        if (connection->wait_release) SetEvent(connection->wait_release);

        HeapFree(GetProcessHeap(), 0, connection);
    }
}