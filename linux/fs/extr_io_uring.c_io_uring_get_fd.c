#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct io_ring_ctx {TYPE_2__* ring_sock; } ;
struct file {int dummy; } ;
struct TYPE_5__ {TYPE_1__* sk; struct file* file; } ;
struct TYPE_4__ {struct io_ring_ctx* sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int O_CLOEXEC ; 
 int O_RDWR ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 struct file* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct io_ring_ctx*,int) ; 
 int /*<<< orphan*/  fd_install (int,struct file*) ; 
 int get_unused_fd_flags (int) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  io_uring_fops ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int sock_create_kern (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  sock_release (TYPE_2__*) ; 

__attribute__((used)) static int io_uring_get_fd(struct io_ring_ctx *ctx)
{
	struct file *file;
	int ret;

#if defined(CONFIG_UNIX)
	ret = sock_create_kern(&init_net, PF_UNIX, SOCK_RAW, IPPROTO_IP,
				&ctx->ring_sock);
	if (ret)
		return ret;
#endif

	ret = get_unused_fd_flags(O_RDWR | O_CLOEXEC);
	if (ret < 0)
		goto err;

	file = anon_inode_getfile("[io_uring]", &io_uring_fops, ctx,
					O_RDWR | O_CLOEXEC);
	if (IS_ERR(file)) {
		put_unused_fd(ret);
		ret = PTR_ERR(file);
		goto err;
	}

#if defined(CONFIG_UNIX)
	ctx->ring_sock->file = file;
	ctx->ring_sock->sk->sk_user_data = ctx;
#endif
	fd_install(ret, file);
	return ret;
err:
#if defined(CONFIG_UNIX)
	sock_release(ctx->ring_sock);
	ctx->ring_sock = NULL;
#endif
	return ret;
}