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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct fuse_file {int /*<<< orphan*/  kh; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  polled_node; int /*<<< orphan*/  count; TYPE_1__ readdir; int /*<<< orphan*/  write_entry; void* release_args; struct fuse_conn* fc; } ;
struct fuse_conn {int /*<<< orphan*/  khctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fuse_file*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unlikely (int) ; 

struct fuse_file *fuse_file_alloc(struct fuse_conn *fc)
{
	struct fuse_file *ff;

	ff = kzalloc(sizeof(struct fuse_file), GFP_KERNEL_ACCOUNT);
	if (unlikely(!ff))
		return NULL;

	ff->fc = fc;
	ff->release_args = kzalloc(sizeof(*ff->release_args),
				   GFP_KERNEL_ACCOUNT);
	if (!ff->release_args) {
		kfree(ff);
		return NULL;
	}

	INIT_LIST_HEAD(&ff->write_entry);
	mutex_init(&ff->readdir.lock);
	refcount_set(&ff->count, 1);
	RB_CLEAR_NODE(&ff->polled_node);
	init_waitqueue_head(&ff->poll_wait);

	ff->kh = atomic64_inc_return(&fc->khctr);

	return ff;
}