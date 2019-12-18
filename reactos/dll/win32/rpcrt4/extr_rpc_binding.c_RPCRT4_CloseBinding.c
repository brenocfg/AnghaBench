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
struct TYPE_4__ {int /*<<< orphan*/  Assoc; int /*<<< orphan*/ * FromConn; scalar_t__ server; } ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  TYPE_1__ RpcBinding ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RPCRT4_ReleaseConnection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RpcAssoc_ReleaseIdleConnection (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

RPC_STATUS RPCRT4_CloseBinding(RpcBinding* Binding, RpcConnection* Connection)
{
  TRACE("(Binding == ^%p)\n", Binding);
  if (!Connection) return RPC_S_OK;
  if (Binding->server) {
    /* don't destroy a connection that is cached in the binding */
    if (Binding->FromConn != Connection)
      RPCRT4_ReleaseConnection(Connection);
  }
  else {
    RpcAssoc_ReleaseIdleConnection(Binding->Assoc, Connection);
  }
  return RPC_S_OK;
}