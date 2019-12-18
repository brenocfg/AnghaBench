#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Endpoint; int /*<<< orphan*/  NetworkAddr; } ;
struct TYPE_5__ {scalar_t__ pipe; } ;
typedef  TYPE_1__ RpcConnection_np ;
typedef  TYPE_2__ RpcConnection ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  I_RpcFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  ncacn_pipe_name (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rpcrt4_conn_open_pipe (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RPC_STATUS rpcrt4_ncacn_np_open(RpcConnection* Connection)
{
  RpcConnection_np *npc = (RpcConnection_np *) Connection;
  RPC_STATUS r;
  LPSTR pname;

  /* already connected? */
  if (npc->pipe)
    return RPC_S_OK;

#ifdef __REACTOS__
  pname = ncacn_pipe_name(Connection->NetworkAddr, Connection->Endpoint);
#else
  pname = ncacn_pipe_name(Connection->Endpoint);
#endif
  r = rpcrt4_conn_open_pipe(Connection, pname, FALSE);
  I_RpcFree(pname);

  return r;
}