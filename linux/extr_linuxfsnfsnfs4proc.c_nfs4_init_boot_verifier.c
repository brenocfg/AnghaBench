#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct nfs_net {int /*<<< orphan*/  boot_time; } ;
struct nfs_client {int /*<<< orphan*/  cl_net; int /*<<< orphan*/  cl_state; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ nfs4_verifier ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4CLNT_PURGE_STATE ; 
 int U32_MAX ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct nfs_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_net_id ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs4_init_boot_verifier(const struct nfs_client *clp,
				    nfs4_verifier *bootverf)
{
	__be32 verf[2];

	if (test_bit(NFS4CLNT_PURGE_STATE, &clp->cl_state)) {
		/* An impossible timestamp guarantees this value
		 * will never match a generated boot time. */
		verf[0] = cpu_to_be32(U32_MAX);
		verf[1] = cpu_to_be32(U32_MAX);
	} else {
		struct nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);
		u64 ns = ktime_to_ns(nn->boot_time);

		verf[0] = cpu_to_be32(ns >> 32);
		verf[1] = cpu_to_be32(ns);
	}
	memcpy(bootverf->data, verf, sizeof(bootverf->data));
}