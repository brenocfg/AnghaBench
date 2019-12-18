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
struct nfs_client {scalar_t__ cl_cons_state; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NFS_CS_READY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

int nfs_client_init_status(const struct nfs_client *clp)
{
	/* called without checking nfs_client_init_is_complete */
	if (clp->cl_cons_state > NFS_CS_READY) {
		WARN_ON_ONCE(1);
		return -EINVAL;
	}
	return clp->cl_cons_state;
}