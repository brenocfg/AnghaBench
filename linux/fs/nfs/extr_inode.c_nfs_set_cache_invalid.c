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
struct nfs_inode {unsigned long cache_validity; } ;
struct inode {TYPE_1__* i_mapping; } ;
struct TYPE_4__ {int (* have_delegation ) (struct inode*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ nrpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_READ ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 unsigned long NFS_INO_DATA_INVAL_DEFER ; 
 unsigned long NFS_INO_INVALID_CHANGE ; 
 unsigned long NFS_INO_INVALID_DATA ; 
 unsigned long NFS_INO_INVALID_OTHER ; 
 unsigned long NFS_INO_INVALID_SIZE ; 
 unsigned long NFS_INO_REVAL_FORCED ; 
 unsigned long NFS_INO_REVAL_PAGECACHE ; 
 TYPE_2__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  nfs_fscache_invalidate (struct inode*) ; 
 int stub1 (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_set_cache_invalid(struct inode *inode, unsigned long flags)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	bool have_delegation = NFS_PROTO(inode)->have_delegation(inode, FMODE_READ);

	if (have_delegation) {
		if (!(flags & NFS_INO_REVAL_FORCED))
			flags &= ~NFS_INO_INVALID_OTHER;
		flags &= ~(NFS_INO_INVALID_CHANGE
				| NFS_INO_INVALID_SIZE
				| NFS_INO_REVAL_PAGECACHE);
	}

	if (inode->i_mapping->nrpages == 0)
		flags &= ~(NFS_INO_INVALID_DATA|NFS_INO_DATA_INVAL_DEFER);
	nfsi->cache_validity |= flags;
	if (flags & NFS_INO_INVALID_DATA)
		nfs_fscache_invalidate(inode);
}