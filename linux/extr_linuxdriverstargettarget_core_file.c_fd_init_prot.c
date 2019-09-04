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
struct se_device {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {TYPE_1__* f_mapping; } ;
struct fd_dev {int fbd_flags; char* fd_dev_name; struct file* fd_prot_file; struct file* fd_file; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOSYS ; 
 int FDBD_HAS_BUFFERED_IO_WCE ; 
 struct fd_dev* FD_DEV (struct se_device*) ; 
 int FD_MAX_DEV_PROT_NAME ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_CREAT ; 
 int O_DSYNC ; 
 int O_LARGEFILE ; 
 int O_RDWR ; 
 int PTR_ERR (struct file*) ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 struct file* filp_open (char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int fd_init_prot(struct se_device *dev)
{
	struct fd_dev *fd_dev = FD_DEV(dev);
	struct file *prot_file, *file = fd_dev->fd_file;
	struct inode *inode;
	int ret, flags = O_RDWR | O_CREAT | O_LARGEFILE | O_DSYNC;
	char buf[FD_MAX_DEV_PROT_NAME];

	if (!file) {
		pr_err("Unable to locate fd_dev->fd_file\n");
		return -ENODEV;
	}

	inode = file->f_mapping->host;
	if (S_ISBLK(inode->i_mode)) {
		pr_err("FILEIO Protection emulation only supported on"
		       " !S_ISBLK\n");
		return -ENOSYS;
	}

	if (fd_dev->fbd_flags & FDBD_HAS_BUFFERED_IO_WCE)
		flags &= ~O_DSYNC;

	snprintf(buf, FD_MAX_DEV_PROT_NAME, "%s.protection",
		 fd_dev->fd_dev_name);

	prot_file = filp_open(buf, flags, 0600);
	if (IS_ERR(prot_file)) {
		pr_err("filp_open(%s) failed\n", buf);
		ret = PTR_ERR(prot_file);
		return ret;
	}
	fd_dev->fd_prot_file = prot_file;

	return 0;
}