#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct p9_fid {int dummy; } ;
struct kiocb {int ki_pos; TYPE_1__* ki_filp; } ;
struct iov_iter {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct p9_fid* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int p9_client_read (struct p9_fid*,int,struct iov_iter*,int*) ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t
v9fs_file_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct p9_fid *fid = iocb->ki_filp->private_data;
	int ret, err = 0;

	p9_debug(P9_DEBUG_VFS, "count %zu offset %lld\n",
		 iov_iter_count(to), iocb->ki_pos);

	ret = p9_client_read(fid, iocb->ki_pos, to, &err);
	if (!ret)
		return err;

	iocb->ki_pos += ret;
	return ret;
}