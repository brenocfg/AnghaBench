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
 scalar_t__ NFS_CS_READY ; 

bool nfs_client_init_is_complete(const struct nfs_client *clp)
{
	return clp->cl_cons_state <= NFS_CS_READY;
}