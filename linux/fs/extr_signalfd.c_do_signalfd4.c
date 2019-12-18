#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct signalfd_ctx {void* sigmask; } ;
struct fd {TYPE_1__* file; } ;
typedef  void* sigset_t ;
struct TYPE_6__ {TYPE_2__* sighand; } ;
struct TYPE_5__ {int /*<<< orphan*/  signalfd_wqh; int /*<<< orphan*/  siglock; } ;
struct TYPE_4__ {int /*<<< orphan*/ * f_op; struct signalfd_ctx* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EBADF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int SFD_CLOEXEC ; 
 int SFD_NONBLOCK ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct signalfd_ctx*,int) ; 
 TYPE_3__* current ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  kfree (struct signalfd_ctx*) ; 
 struct signalfd_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigdelsetmask (void**,int) ; 
 int sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signalfd_fops ; 
 int /*<<< orphan*/  signotset (void**) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_signalfd4(int ufd, sigset_t *mask, int flags)
{
	struct signalfd_ctx *ctx;

	/* Check the SFD_* constants for consistency.  */
	BUILD_BUG_ON(SFD_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON(SFD_NONBLOCK != O_NONBLOCK);

	if (flags & ~(SFD_CLOEXEC | SFD_NONBLOCK))
		return -EINVAL;

	sigdelsetmask(mask, sigmask(SIGKILL) | sigmask(SIGSTOP));
	signotset(mask);

	if (ufd == -1) {
		ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
		if (!ctx)
			return -ENOMEM;

		ctx->sigmask = *mask;

		/*
		 * When we call this, the initialization must be complete, since
		 * anon_inode_getfd() will install the fd.
		 */
		ufd = anon_inode_getfd("[signalfd]", &signalfd_fops, ctx,
				       O_RDWR | (flags & (O_CLOEXEC | O_NONBLOCK)));
		if (ufd < 0)
			kfree(ctx);
	} else {
		struct fd f = fdget(ufd);
		if (!f.file)
			return -EBADF;
		ctx = f.file->private_data;
		if (f.file->f_op != &signalfd_fops) {
			fdput(f);
			return -EINVAL;
		}
		spin_lock_irq(&current->sighand->siglock);
		ctx->sigmask = *mask;
		spin_unlock_irq(&current->sighand->siglock);

		wake_up(&current->sighand->signalfd_wqh);
		fdput(f);
	}

	return ufd;
}