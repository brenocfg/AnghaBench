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
struct fuse_dev {int /*<<< orphan*/  entry; int /*<<< orphan*/  pq; int /*<<< orphan*/  fc; } ;
struct fuse_conn {int /*<<< orphan*/  lock; int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fuse_conn_get (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_pqueue_init (int /*<<< orphan*/ *) ; 
 struct fuse_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct fuse_dev *fuse_dev_alloc(struct fuse_conn *fc)
{
	struct fuse_dev *fud;

	fud = kzalloc(sizeof(struct fuse_dev), GFP_KERNEL);
	if (fud) {
		fud->fc = fuse_conn_get(fc);
		fuse_pqueue_init(&fud->pq);

		spin_lock(&fc->lock);
		list_add_tail(&fud->entry, &fc->devices);
		spin_unlock(&fc->lock);
	}

	return fud;
}