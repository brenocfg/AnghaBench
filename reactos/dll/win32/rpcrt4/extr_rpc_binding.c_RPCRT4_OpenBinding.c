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
struct TYPE_4__ {int /*<<< orphan*/ * FromConn; int /*<<< orphan*/  CookieAuth; int /*<<< orphan*/  QOS; int /*<<< orphan*/  AuthInfo; int /*<<< orphan*/  Assoc; int /*<<< orphan*/  server; } ;
typedef  int /*<<< orphan*/  RpcConnection ;
typedef  TYPE_1__ RpcBinding ;
typedef  int /*<<< orphan*/  RPC_SYNTAX_IDENTIFIER ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  RPC_S_INTERNAL_ERROR ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RpcAssoc_GetClientConnection (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

RPC_STATUS RPCRT4_OpenBinding(RpcBinding* Binding, RpcConnection** Connection,
                              const RPC_SYNTAX_IDENTIFIER *TransferSyntax,
                              const RPC_SYNTAX_IDENTIFIER *InterfaceId, BOOL *from_cache)
{
  TRACE("(Binding == ^%p)\n", Binding);

  if (!Binding->server) {
     return RpcAssoc_GetClientConnection(Binding->Assoc, InterfaceId,
         TransferSyntax, Binding->AuthInfo, Binding->QOS, Binding->CookieAuth, Connection, from_cache);
  } else {
    /* we already have a connection with acceptable binding, so use it */
    if (Binding->FromConn) {
      *Connection = Binding->FromConn;
      return RPC_S_OK;
    } else {
       ERR("no connection in binding\n");
       return RPC_S_INTERNAL_ERROR;
    }
  }
}