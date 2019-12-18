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
struct nfs4_ol_stateid {int /*<<< orphan*/  st_mutex; int /*<<< orphan*/  st_stid; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_STATEID_MUTEX ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_verify_open_stid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_lock_ol_stateid(struct nfs4_ol_stateid *stp)
{
	__be32 ret;

	mutex_lock_nested(&stp->st_mutex, LOCK_STATEID_MUTEX);
	ret = nfsd4_verify_open_stid(&stp->st_stid);
	if (ret != nfs_ok)
		mutex_unlock(&stp->st_mutex);
	return ret;
}