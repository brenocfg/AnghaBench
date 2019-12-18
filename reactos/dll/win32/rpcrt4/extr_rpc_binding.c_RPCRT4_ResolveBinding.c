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
struct TYPE_4__ {int /*<<< orphan*/ * Assoc; int /*<<< orphan*/  NetworkOptions; int /*<<< orphan*/  Endpoint; int /*<<< orphan*/  NetworkAddr; int /*<<< orphan*/  Protseq; } ;
typedef  TYPE_1__ RpcBinding ;
typedef  scalar_t__ RPC_STATUS ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 scalar_t__ RPCRT4_GetAssociation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RPCRT4_strdupA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCRT4_strfree (int /*<<< orphan*/ ) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  RpcAssoc_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 

RPC_STATUS RPCRT4_ResolveBinding(RpcBinding* Binding, LPCSTR Endpoint)
{
  RPC_STATUS status;

  TRACE("(RpcBinding == ^%p, EndPoint == \"%s\"\n", Binding, Endpoint);

  RPCRT4_strfree(Binding->Endpoint);
  Binding->Endpoint = RPCRT4_strdupA(Endpoint);

  if (Binding->Assoc) RpcAssoc_Release(Binding->Assoc);
  Binding->Assoc = NULL;
  status = RPCRT4_GetAssociation(Binding->Protseq, Binding->NetworkAddr,
                                 Binding->Endpoint, Binding->NetworkOptions,
                                 &Binding->Assoc);
  if (status != RPC_S_OK)
      return status;

  return RPC_S_OK;
}