#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfs_client {int dummy; } ;
struct nfs4_state_recovery_ops {int (* reclaim_complete ) (struct nfs_client*,struct cred const*) ;} ;
struct cred {int dummy; } ;

/* Variables and functions */
 int stub1 (struct nfs_client*,struct cred const*) ; 

__attribute__((used)) static int nfs4_reclaim_complete(struct nfs_client *clp,
				 const struct nfs4_state_recovery_ops *ops,
				 const struct cred *cred)
{
	/* Notify the server we're done reclaiming our state */
	if (ops->reclaim_complete)
		return ops->reclaim_complete(clp, cred);
	return 0;
}