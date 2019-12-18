#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tv_nsec; } ;
struct nfsd4_layoutcommit {scalar_t__ lc_last_wr; TYPE_3__ lc_mtime; } ;
struct iomap {int dummy; } ;
struct inode {TYPE_2__* i_sb; int /*<<< orphan*/  i_mtime; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; TYPE_3__ ia_mtime; TYPE_3__ ia_ctime; TYPE_3__ ia_atime; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {TYPE_1__* s_export_op; } ;
struct TYPE_5__ {int (* commit_blocks ) (struct inode*,struct iomap*,int,struct iattr*) ;} ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 int ATTR_SIZE ; 
 scalar_t__ UTIME_NOW ; 
 TYPE_3__ current_time (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct iomap*) ; 
 int /*<<< orphan*/  nfserrno (int) ; 
 int stub1 (struct inode*,struct iomap*,int,struct iattr*) ; 
 scalar_t__ timespec64_compare (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd4_block_commit_blocks(struct inode *inode, struct nfsd4_layoutcommit *lcp,
		struct iomap *iomaps, int nr_iomaps)
{
	loff_t new_size = lcp->lc_last_wr + 1;
	struct iattr iattr = { .ia_valid = 0 };
	int error;

	if (lcp->lc_mtime.tv_nsec == UTIME_NOW ||
	    timespec64_compare(&lcp->lc_mtime, &inode->i_mtime) < 0)
		lcp->lc_mtime = current_time(inode);
	iattr.ia_valid |= ATTR_ATIME | ATTR_CTIME | ATTR_MTIME;
	iattr.ia_atime = iattr.ia_ctime = iattr.ia_mtime = lcp->lc_mtime;

	if (new_size > i_size_read(inode)) {
		iattr.ia_valid |= ATTR_SIZE;
		iattr.ia_size = new_size;
	}

	error = inode->i_sb->s_export_op->commit_blocks(inode, iomaps,
			nr_iomaps, &iattr);
	kfree(iomaps);
	return nfserrno(error);
}