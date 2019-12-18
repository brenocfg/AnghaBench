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
struct userfaultfd_ctx {scalar_t__ state; } ;
struct file {struct userfaultfd_ctx* private_data; } ;

/* Variables and functions */
 long EINVAL ; 
#define  UFFDIO_API 133 
#define  UFFDIO_COPY 132 
#define  UFFDIO_REGISTER 131 
#define  UFFDIO_UNREGISTER 130 
#define  UFFDIO_WAKE 129 
#define  UFFDIO_ZEROPAGE 128 
 scalar_t__ UFFD_STATE_WAIT_API ; 
 int userfaultfd_api (struct userfaultfd_ctx*,unsigned long) ; 
 int userfaultfd_copy (struct userfaultfd_ctx*,unsigned long) ; 
 int userfaultfd_register (struct userfaultfd_ctx*,unsigned long) ; 
 int userfaultfd_unregister (struct userfaultfd_ctx*,unsigned long) ; 
 int userfaultfd_wake (struct userfaultfd_ctx*,unsigned long) ; 
 int userfaultfd_zeropage (struct userfaultfd_ctx*,unsigned long) ; 

__attribute__((used)) static long userfaultfd_ioctl(struct file *file, unsigned cmd,
			      unsigned long arg)
{
	int ret = -EINVAL;
	struct userfaultfd_ctx *ctx = file->private_data;

	if (cmd != UFFDIO_API && ctx->state == UFFD_STATE_WAIT_API)
		return -EINVAL;

	switch(cmd) {
	case UFFDIO_API:
		ret = userfaultfd_api(ctx, arg);
		break;
	case UFFDIO_REGISTER:
		ret = userfaultfd_register(ctx, arg);
		break;
	case UFFDIO_UNREGISTER:
		ret = userfaultfd_unregister(ctx, arg);
		break;
	case UFFDIO_WAKE:
		ret = userfaultfd_wake(ctx, arg);
		break;
	case UFFDIO_COPY:
		ret = userfaultfd_copy(ctx, arg);
		break;
	case UFFDIO_ZEROPAGE:
		ret = userfaultfd_zeropage(ctx, arg);
		break;
	}
	return ret;
}