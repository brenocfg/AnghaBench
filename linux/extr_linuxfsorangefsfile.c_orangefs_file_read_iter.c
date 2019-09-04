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
struct kiocb {int /*<<< orphan*/  ki_pos; int /*<<< orphan*/  private; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  reads; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GOSSIP_FILE_DEBUG ; 
 int /*<<< orphan*/  ORANGEFS_IO_READ ; 
 int /*<<< orphan*/  do_readv_writev (int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ *,struct iov_iter*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ orangefs_stats ; 

__attribute__((used)) static ssize_t orangefs_file_read_iter(struct kiocb *iocb, struct iov_iter *iter)
{
	struct file *file = iocb->ki_filp;
	loff_t pos = iocb->ki_pos;
	ssize_t rc = 0;

	BUG_ON(iocb->private);

	gossip_debug(GOSSIP_FILE_DEBUG, "orangefs_file_read_iter\n");

	orangefs_stats.reads++;

	rc = do_readv_writev(ORANGEFS_IO_READ, file, &pos, iter);
	iocb->ki_pos = pos;

	return rc;
}