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
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  SecInvalidateHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ SecIsValidHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  rpcrt4_conn_close (TYPE_1__*) ; 

RPC_STATUS RPCRT4_CloseConnection(RpcConnection* Connection)
{
  TRACE("(Connection == ^%p)\n", Connection);
  if (SecIsValidHandle(&Connection->ctx))
  {
    DeleteSecurityContext(&Connection->ctx);
    SecInvalidateHandle(&Connection->ctx);
  }
  rpcrt4_conn_close(Connection);
  return RPC_S_OK;
}