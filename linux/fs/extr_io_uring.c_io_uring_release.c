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
struct io_ring_ctx {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct io_ring_ctx* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_ring_ctx_wait_and_kill (struct io_ring_ctx*) ; 

__attribute__((used)) static int io_uring_release(struct inode *inode, struct file *file)
{
	struct io_ring_ctx *ctx = file->private_data;

	file->private_data = NULL;
	io_ring_ctx_wait_and_kill(ctx);
	return 0;
}