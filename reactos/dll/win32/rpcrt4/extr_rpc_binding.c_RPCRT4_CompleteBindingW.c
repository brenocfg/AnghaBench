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
struct TYPE_4__ {int /*<<< orphan*/  Assoc; int /*<<< orphan*/  NetworkOptions; void* Endpoint; void* NetworkAddr; int /*<<< orphan*/  Protseq; } ;
typedef  TYPE_1__ RpcBinding ;
typedef  scalar_t__ RPC_STATUS ;
typedef  char* LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RPCRT4_GetAssociation (int /*<<< orphan*/ ,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RPCRT4_strdupW (char*) ; 
 void* RPCRT4_strdupWtoA (char*) ; 
 int /*<<< orphan*/  RPCRT4_strfree (void*) ; 
 scalar_t__ RPC_S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 

__attribute__((used)) static RPC_STATUS RPCRT4_CompleteBindingW(RpcBinding* Binding, LPCWSTR NetworkAddr,
                                          LPCWSTR Endpoint, LPCWSTR NetworkOptions)
{
  RPC_STATUS status;

  TRACE("(RpcBinding == ^%p, NetworkAddr == %s, EndPoint == %s, NetworkOptions == %s)\n", Binding, 
   debugstr_w(NetworkAddr), debugstr_w(Endpoint), debugstr_w(NetworkOptions));

  RPCRT4_strfree(Binding->NetworkAddr);
  Binding->NetworkAddr = RPCRT4_strdupWtoA(NetworkAddr);
  RPCRT4_strfree(Binding->Endpoint);
  Binding->Endpoint = RPCRT4_strdupWtoA(Endpoint);
  HeapFree(GetProcessHeap(), 0, Binding->NetworkOptions);
  Binding->NetworkOptions = RPCRT4_strdupW(NetworkOptions);

  /* only attempt to get an association if the binding is complete */
  if (Endpoint && Endpoint[0] != '\0')
  {
    status = RPCRT4_GetAssociation(Binding->Protseq, Binding->NetworkAddr,
                                   Binding->Endpoint, Binding->NetworkOptions,
                                   &Binding->Assoc);
    if (status != RPC_S_OK)
        return status;
  }

  return RPC_S_OK;
}