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
struct connection_ops {TYPE_1__* (* alloc ) () ;} ;
struct TYPE_5__ {int ref; int NextCallId; int /*<<< orphan*/  protseq_entry; int /*<<< orphan*/  conn_pool_entry; int /*<<< orphan*/ * QOS; int /*<<< orphan*/  auth_context_id; int /*<<< orphan*/ * AuthInfo; int /*<<< orphan*/  ctx; int /*<<< orphan*/  MaxTransmissionSize; void* CookieAuth; void* NetworkOptions; void* Endpoint; void* NetworkAddr; struct connection_ops const* ops; int /*<<< orphan*/  server; } ;
typedef  int /*<<< orphan*/  RpcQualityOfService ;
typedef  TYPE_1__ RpcConnection ;
typedef  int /*<<< orphan*/  RpcAuthInfo ;
typedef  int /*<<< orphan*/  RPC_STATUS ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 void* RPCRT4_strdupA (int /*<<< orphan*/ ) ; 
 void* RPCRT4_strdupW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  RPC_S_OK ; 
 int /*<<< orphan*/  RPC_S_PROTSEQ_NOT_SUPPORTED ; 
 int /*<<< orphan*/  RpcAuthInfo_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RpcQualityOfService_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SecInvalidateHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 struct connection_ops* rpcrt4_get_conn_protseq_ops (int /*<<< orphan*/ ) ; 
 TYPE_1__* stub1 () ; 

RPC_STATUS RPCRT4_CreateConnection(RpcConnection** Connection, BOOL server,
    LPCSTR Protseq, LPCSTR NetworkAddr, LPCSTR Endpoint,
    LPCWSTR NetworkOptions, RpcAuthInfo* AuthInfo, RpcQualityOfService *QOS, LPCWSTR CookieAuth)
{
  static LONG next_id;
  const struct connection_ops *ops;
  RpcConnection* NewConnection;

  ops = rpcrt4_get_conn_protseq_ops(Protseq);
  if (!ops)
  {
    FIXME("not supported for protseq %s\n", Protseq);
    return RPC_S_PROTSEQ_NOT_SUPPORTED;
  }

  NewConnection = ops->alloc();
  NewConnection->ref = 1;
  NewConnection->server = server;
  NewConnection->ops = ops;
  NewConnection->NetworkAddr = RPCRT4_strdupA(NetworkAddr);
  NewConnection->Endpoint = RPCRT4_strdupA(Endpoint);
  NewConnection->NetworkOptions = RPCRT4_strdupW(NetworkOptions);
  NewConnection->CookieAuth = RPCRT4_strdupW(CookieAuth);
  NewConnection->MaxTransmissionSize = RPC_MAX_PACKET_SIZE;
  NewConnection->NextCallId = 1;

  SecInvalidateHandle(&NewConnection->ctx);
  if (AuthInfo) RpcAuthInfo_AddRef(AuthInfo);
  NewConnection->AuthInfo = AuthInfo;
  NewConnection->auth_context_id = InterlockedIncrement( &next_id );
  if (QOS) RpcQualityOfService_AddRef(QOS);
  NewConnection->QOS = QOS;

  list_init(&NewConnection->conn_pool_entry);
  list_init(&NewConnection->protseq_entry);

  TRACE("connection: %p\n", NewConnection);
  *Connection = NewConnection;

  return RPC_S_OK;
}