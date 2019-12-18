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
typedef  int u32 ;
struct nfs_access_entry {int mask; struct cred const* cred; } ;
struct nfs4_state {TYPE_2__* inode; } ;
struct TYPE_3__ {scalar_t__ access_supported; int /*<<< orphan*/  access_result; } ;
struct nfs4_opendata {TYPE_1__ o_res; int /*<<< orphan*/  file_created; } ;
struct cred {int dummy; } ;
typedef  int fmode_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int EACCES ; 
 int FMODE_READ ; 
 int NFS4_ACCESS_EXECUTE ; 
 int NFS4_ACCESS_LOOKUP ; 
 int NFS4_ACCESS_READ ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int __FMODE_EXEC ; 
 int /*<<< orphan*/  nfs_access_add_cache (TYPE_2__*,struct nfs_access_entry*) ; 
 int /*<<< orphan*/  nfs_access_set_mask (struct nfs_access_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs4_opendata_access(const struct cred *cred,
				struct nfs4_opendata *opendata,
				struct nfs4_state *state, fmode_t fmode,
				int openflags)
{
	struct nfs_access_entry cache;
	u32 mask, flags;

	/* access call failed or for some reason the server doesn't
	 * support any access modes -- defer access call until later */
	if (opendata->o_res.access_supported == 0)
		return 0;

	mask = 0;
	/*
	 * Use openflags to check for exec, because fmode won't
	 * always have FMODE_EXEC set when file open for exec.
	 */
	if (openflags & __FMODE_EXEC) {
		/* ONLY check for exec rights */
		if (S_ISDIR(state->inode->i_mode))
			mask = NFS4_ACCESS_LOOKUP;
		else
			mask = NFS4_ACCESS_EXECUTE;
	} else if ((fmode & FMODE_READ) && !opendata->file_created)
		mask = NFS4_ACCESS_READ;

	cache.cred = cred;
	nfs_access_set_mask(&cache, opendata->o_res.access_result);
	nfs_access_add_cache(state->inode, &cache);

	flags = NFS4_ACCESS_READ | NFS4_ACCESS_EXECUTE | NFS4_ACCESS_LOOKUP;
	if ((mask & ~cache.mask & flags) == 0)
		return 0;

	return -EACCES;
}