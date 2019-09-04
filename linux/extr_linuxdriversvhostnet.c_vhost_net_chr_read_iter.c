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
struct vhost_dev {int dummy; } ;
struct vhost_net {struct vhost_dev dev; } ;
struct kiocb {struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct file {int f_flags; struct vhost_net* private_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int /*<<< orphan*/  vhost_chr_read_iter (struct vhost_dev*,struct iov_iter*,int) ; 

__attribute__((used)) static ssize_t vhost_net_chr_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct file *file = iocb->ki_filp;
	struct vhost_net *n = file->private_data;
	struct vhost_dev *dev = &n->dev;
	int noblock = file->f_flags & O_NONBLOCK;

	return vhost_chr_read_iter(dev, to, noblock);
}