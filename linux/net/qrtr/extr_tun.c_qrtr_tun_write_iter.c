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
struct qrtr_tun {int /*<<< orphan*/  ep; } ;
struct kiocb {struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct file {struct qrtr_tun* private_data; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EFAULT ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  copy_from_iter_full (void*,size_t,struct iov_iter*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ qrtr_endpoint_post (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static ssize_t qrtr_tun_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *filp = iocb->ki_filp;
	struct qrtr_tun *tun = filp->private_data;
	size_t len = iov_iter_count(from);
	ssize_t ret;
	void *kbuf;

	kbuf = kzalloc(len, GFP_KERNEL);
	if (!kbuf)
		return -ENOMEM;

	if (!copy_from_iter_full(kbuf, len, from)) {
		kfree(kbuf);
		return -EFAULT;
	}

	ret = qrtr_endpoint_post(&tun->ep, kbuf, len);

	kfree(kbuf);
	return ret < 0 ? ret : len;
}