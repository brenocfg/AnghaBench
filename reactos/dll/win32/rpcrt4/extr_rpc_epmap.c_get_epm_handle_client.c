#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* endpoint; int /*<<< orphan*/  protseq; } ;
struct TYPE_10__ {int /*<<< orphan*/ * AuthInfo; int /*<<< orphan*/  Protseq; scalar_t__ server; } ;
typedef  TYPE_1__ RpcBinding ;
typedef  scalar_t__ RPC_STATUS ;
typedef  TYPE_1__* RPC_BINDING_HANDLE ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_5__*) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCRT4_ResolveBinding (TYPE_1__*,char const*) ; 
 scalar_t__ RPC_S_INVALID_BINDING ; 
 scalar_t__ RPC_S_OK ; 
 scalar_t__ RPC_S_PROTSEQ_NOT_SUPPORTED ; 
 int /*<<< orphan*/  RpcAuthInfo_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ RpcBindingCopy (TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 
 TYPE_5__* epm_endpoints ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RPC_STATUS get_epm_handle_client(RPC_BINDING_HANDLE handle, RPC_BINDING_HANDLE *epm_handle)
{
    RpcBinding *bind = handle;
    const char * pszEndpoint = NULL;
    RPC_STATUS status;
    RpcBinding* epm_bind;
    unsigned int i;

    if (bind->server)
        return RPC_S_INVALID_BINDING;

    for (i = 0; i < ARRAY_SIZE(epm_endpoints); i++)
        if (!strcmp(bind->Protseq, epm_endpoints[i].protseq))
            pszEndpoint = epm_endpoints[i].endpoint;

    if (!pszEndpoint)
    {
        FIXME("no endpoint for the endpoint-mapper found for protseq %s\n", debugstr_a(bind->Protseq));
        return RPC_S_PROTSEQ_NOT_SUPPORTED;
    }

    status = RpcBindingCopy(handle, epm_handle);
    if (status != RPC_S_OK) return status;

    epm_bind = *epm_handle;
    if (epm_bind->AuthInfo)
    {
        /* don't bother with authenticating against the EPM by default
        * (see EnableAuthEpResolution registry value) */
        RpcAuthInfo_Release(epm_bind->AuthInfo);
        epm_bind->AuthInfo = NULL;
    }
    RPCRT4_ResolveBinding(epm_bind, pszEndpoint);
    TRACE("RPC_S_OK\n");
    return RPC_S_OK;
}