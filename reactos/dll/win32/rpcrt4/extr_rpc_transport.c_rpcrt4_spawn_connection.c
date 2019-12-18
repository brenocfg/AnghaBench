#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* protseq; int /*<<< orphan*/  protseq_entry; int /*<<< orphan*/  CookieAuth; int /*<<< orphan*/  QOS; int /*<<< orphan*/  AuthInfo; int /*<<< orphan*/  Endpoint; int /*<<< orphan*/  NetworkAddr; int /*<<< orphan*/  server; } ;
struct TYPE_9__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  connections; } ;
typedef  TYPE_2__ RpcConnection ;
typedef  scalar_t__ RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ RPCRT4_CreateConnection (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpcrt4_conn_get_name (TYPE_2__*) ; 
 int /*<<< orphan*/  rpcrt4_conn_handoff (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static RpcConnection *rpcrt4_spawn_connection(RpcConnection *old_connection)
{
    RpcConnection *connection;
    RPC_STATUS err;

    err = RPCRT4_CreateConnection(&connection, old_connection->server, rpcrt4_conn_get_name(old_connection),
                                  old_connection->NetworkAddr, old_connection->Endpoint, NULL,
                                  old_connection->AuthInfo, old_connection->QOS, old_connection->CookieAuth);
    if (err != RPC_S_OK)
        return NULL;

    rpcrt4_conn_handoff(old_connection, connection);
    if (old_connection->protseq)
    {
        EnterCriticalSection(&old_connection->protseq->cs);
        connection->protseq = old_connection->protseq;
        list_add_tail(&old_connection->protseq->connections, &connection->protseq_entry);
        LeaveCriticalSection(&old_connection->protseq->cs);
    }
    return connection;
}