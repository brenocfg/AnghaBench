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
struct nfs_server {int dummy; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int NFS4ERR_BAD_STATEID ; 

__attribute__((used)) static int nfs40_test_and_free_expired_stateid(struct nfs_server *server,
		nfs4_stateid *stateid,
		const struct cred *cred)
{
	return -NFS4ERR_BAD_STATEID;
}