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
struct inode {struct ffs_epfile* i_private; } ;
struct file {int dummy; } ;
struct ffs_epfile {int /*<<< orphan*/  ffs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  __ffs_epfile_read_buffer_free (struct ffs_epfile*) ; 
 int /*<<< orphan*/  ffs_data_closed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffs_epfile_release(struct inode *inode, struct file *file)
{
	struct ffs_epfile *epfile = inode->i_private;

	ENTER();

	__ffs_epfile_read_buffer_free(epfile);
	ffs_data_closed(epfile->ffs);

	return 0;
}