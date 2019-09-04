#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfs_client {TYPE_2__* cl_rpcclient; } ;
typedef  scalar_t__ rpc_authflavor_t ;
struct TYPE_4__ {TYPE_1__* cl_auth; } ;
struct TYPE_3__ {scalar_t__ au_flavor; } ;

/* Variables and functions */
 scalar_t__ RPC_AUTH_GSS_KRB5I ; 
 scalar_t__ RPC_AUTH_GSS_KRB5P ; 

__attribute__((used)) static bool _nfs4_is_integrity_protected(struct nfs_client *clp)
{
	rpc_authflavor_t flavor = clp->cl_rpcclient->cl_auth->au_flavor;
	return (flavor == RPC_AUTH_GSS_KRB5I) || (flavor == RPC_AUTH_GSS_KRB5P);
}