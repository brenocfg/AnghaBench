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
struct kiocb {TYPE_2__* ki_filp; } ;
struct iov_iter {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* f_mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ IS_DAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_dax_write_iter (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  generic_file_write_iter (struct kiocb*,struct iov_iter*) ; 

__attribute__((used)) static ssize_t ext2_file_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
#ifdef CONFIG_FS_DAX
	if (IS_DAX(iocb->ki_filp->f_mapping->host))
		return ext2_dax_write_iter(iocb, from);
#endif
	return generic_file_write_iter(iocb, from);
}