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
struct nfs_subversion {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct nfs_subversion* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct nfs_subversion*) ; 
 struct nfs_subversion* find_nfs_version (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_version_mutex ; 
 int /*<<< orphan*/  request_module (char*,unsigned int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct nfs_subversion *get_nfs_version(unsigned int version)
{
	struct nfs_subversion *nfs = find_nfs_version(version);

	if (IS_ERR(nfs)) {
		mutex_lock(&nfs_version_mutex);
		request_module("nfsv%d", version);
		nfs = find_nfs_version(version);
		mutex_unlock(&nfs_version_mutex);
	}

	if (!IS_ERR(nfs) && !try_module_get(nfs->owner))
		return ERR_PTR(-EAGAIN);
	return nfs;
}