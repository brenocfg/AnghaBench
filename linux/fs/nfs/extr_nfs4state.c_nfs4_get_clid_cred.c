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
struct cred {int dummy; } ;

/* Variables and functions */
 struct cred* nfs4_get_machine_cred (struct nfs_client*) ; 

const struct cred *nfs4_get_clid_cred(struct nfs_client *clp)
{
	const struct cred *cred;

	cred = nfs4_get_machine_cred(clp);
	return cred;
}