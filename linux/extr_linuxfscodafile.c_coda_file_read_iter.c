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
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct file {int dummy; } ;
struct coda_file_info {scalar_t__ cfi_magic; int /*<<< orphan*/  cfi_container; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct coda_file_info* CODA_FTOC (struct file*) ; 
 scalar_t__ CODA_MAGIC ; 
 int /*<<< orphan*/  vfs_iter_read (int /*<<< orphan*/ ,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
coda_file_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct file *coda_file = iocb->ki_filp;
	struct coda_file_info *cfi = CODA_FTOC(coda_file);

	BUG_ON(!cfi || cfi->cfi_magic != CODA_MAGIC);

	return vfs_iter_read(cfi->cfi_container, to, &iocb->ki_pos, 0);
}