#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct orangefs_read_options {int /*<<< orphan*/  blksiz; } ;
struct kiocb {TYPE_4__* ki_filp; } ;
struct iov_iter {int /*<<< orphan*/  count; } ;
typedef  int ssize_t ;
struct TYPE_7__ {struct orangefs_read_options* private_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_rwsem; } ;
struct TYPE_5__ {int /*<<< orphan*/  reads; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 TYPE_2__* file_inode (TYPE_4__*) ; 
 int generic_file_read_iter (struct kiocb*,struct iov_iter*) ; 
 struct orangefs_read_options* kmalloc (int,int /*<<< orphan*/ ) ; 
 int orangefs_revalidate_mapping (TYPE_2__*) ; 
 TYPE_1__ orangefs_stats ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t orangefs_file_read_iter(struct kiocb *iocb,
    struct iov_iter *iter)
{
	int ret;
	struct orangefs_read_options *ro;

	orangefs_stats.reads++;

	/*
	 * Remember how they set "count" in read(2) or pread(2) or whatever -
	 * users can use count as a knob to control orangefs io size and later
	 * we can try to help them fill as many pages as possible in readpage.
	 */
	if (!iocb->ki_filp->private_data) {
		iocb->ki_filp->private_data = kmalloc(sizeof *ro, GFP_KERNEL);
		if (!iocb->ki_filp->private_data)
			return(ENOMEM);
		ro = iocb->ki_filp->private_data;
		ro->blksiz = iter->count;
	}

	down_read(&file_inode(iocb->ki_filp)->i_rwsem);
	ret = orangefs_revalidate_mapping(file_inode(iocb->ki_filp));
	if (ret)
		goto out;

	ret = generic_file_read_iter(iocb, iter);
out:
	up_read(&file_inode(iocb->ki_filp)->i_rwsem);
	return ret;
}