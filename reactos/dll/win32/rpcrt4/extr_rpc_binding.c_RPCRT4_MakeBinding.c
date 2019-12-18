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
struct TYPE_8__ {TYPE_1__* FromConn; void* Endpoint; void* NetworkAddr; void* Protseq; } ;
struct TYPE_7__ {int /*<<< orphan*/  Endpoint; int /*<<< orphan*/  NetworkAddr; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ RpcConnection ;
typedef  TYPE_2__ RpcBinding ;
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  RPCRT4_AllocBinding (TYPE_2__**,int /*<<< orphan*/ ) ; 
 void* RPCRT4_strdupA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  rpcrt4_conn_get_name (TYPE_1__*) ; 

RPC_STATUS RPCRT4_MakeBinding(RpcBinding** Binding, RpcConnection* Connection)
{
  RpcBinding* NewBinding;
  TRACE("(RpcBinding == ^%p, Connection == ^%p)\n", Binding, Connection);

  RPCRT4_AllocBinding(&NewBinding, Connection->server);
  NewBinding->Protseq = RPCRT4_strdupA(rpcrt4_conn_get_name(Connection));
  NewBinding->NetworkAddr = RPCRT4_strdupA(Connection->NetworkAddr);
  NewBinding->Endpoint = RPCRT4_strdupA(Connection->Endpoint);
  NewBinding->FromConn = Connection;

  TRACE("binding: %p\n", NewBinding);
  *Binding = NewBinding;

  return RPC_S_OK;
}