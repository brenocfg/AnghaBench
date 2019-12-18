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
struct eventfd_ctx {unsigned int count; int flags; int /*<<< orphan*/  id; int /*<<< orphan*/  wqh; int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ EFD_CLOEXEC ; 
 int EFD_FLAGS_SET ; 
 scalar_t__ EFD_NONBLOCK ; 
 int EFD_SHARED_FCNTL_FLAGS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ O_CLOEXEC ; 
 scalar_t__ O_NONBLOCK ; 
 int O_RDWR ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct eventfd_ctx*,int) ; 
 int /*<<< orphan*/  eventfd_fops ; 
 int /*<<< orphan*/  eventfd_free_ctx (struct eventfd_ctx*) ; 
 int /*<<< orphan*/  eventfd_ida ; 
 int /*<<< orphan*/  ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct eventfd_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_eventfd(unsigned int count, int flags)
{
	struct eventfd_ctx *ctx;
	int fd;

	/* Check the EFD_* constants for consistency.  */
	BUILD_BUG_ON(EFD_CLOEXEC != O_CLOEXEC);
	BUILD_BUG_ON(EFD_NONBLOCK != O_NONBLOCK);

	if (flags & ~EFD_FLAGS_SET)
		return -EINVAL;

	ctx = kmalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	kref_init(&ctx->kref);
	init_waitqueue_head(&ctx->wqh);
	ctx->count = count;
	ctx->flags = flags;
	ctx->id = ida_simple_get(&eventfd_ida, 0, 0, GFP_KERNEL);

	fd = anon_inode_getfd("[eventfd]", &eventfd_fops, ctx,
			      O_RDWR | (flags & EFD_SHARED_FCNTL_FLAGS));
	if (fd < 0)
		eventfd_free_ctx(ctx);

	return fd;
}