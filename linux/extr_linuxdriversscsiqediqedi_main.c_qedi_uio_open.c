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
struct uio_info {struct qedi_uio_dev* priv; } ;
struct qedi_uio_dev {int uio_dev; struct qedi_ctx* qedi; } ;
struct qedi_ctx {int /*<<< orphan*/  flags; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EBUSY ; 
 int EPERM ; 
 int /*<<< orphan*/  UIO_DEV_OPENED ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  qedi_reset_uio_rings (struct qedi_uio_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qedi_uio_open(struct uio_info *uinfo, struct inode *inode)
{
	struct qedi_uio_dev *udev = uinfo->priv;
	struct qedi_ctx *qedi = udev->qedi;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;

	if (udev->uio_dev != -1)
		return -EBUSY;

	rtnl_lock();
	udev->uio_dev = iminor(inode);
	qedi_reset_uio_rings(udev);
	set_bit(UIO_DEV_OPENED, &qedi->flags);
	rtnl_unlock();

	return 0;
}