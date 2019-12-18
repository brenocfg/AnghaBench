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
struct kiocb {scalar_t__ ki_pos; TYPE_2__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct fuse_conn {scalar_t__ auto_inval_data; } ;
typedef  int ssize_t ;
struct TYPE_4__ {TYPE_1__* f_mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int fuse_update_attributes (struct inode*,TYPE_2__*) ; 
 int generic_file_read_iter (struct kiocb*,struct iov_iter*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 

__attribute__((used)) static ssize_t fuse_cache_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct inode *inode = iocb->ki_filp->f_mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);

	/*
	 * In auto invalidate mode, always update attributes on read.
	 * Otherwise, only update if we attempt to read past EOF (to ensure
	 * i_size is up to date).
	 */
	if (fc->auto_inval_data ||
	    (iocb->ki_pos + iov_iter_count(to) > i_size_read(inode))) {
		int err;
		err = fuse_update_attributes(inode, iocb->ki_filp);
		if (err)
			return err;
	}

	return generic_file_read_iter(iocb, to);
}