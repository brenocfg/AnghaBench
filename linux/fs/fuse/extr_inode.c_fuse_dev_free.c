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
struct TYPE_2__ {struct fuse_dev* processing; } ;
struct fuse_dev {TYPE_1__ pq; int /*<<< orphan*/  entry; struct fuse_conn* fc; } ;
struct fuse_conn {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_conn_put (struct fuse_conn*) ; 
 int /*<<< orphan*/  kfree (struct fuse_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void fuse_dev_free(struct fuse_dev *fud)
{
	struct fuse_conn *fc = fud->fc;

	if (fc) {
		spin_lock(&fc->lock);
		list_del(&fud->entry);
		spin_unlock(&fc->lock);

		fuse_conn_put(fc);
	}
	kfree(fud->pq.processing);
	kfree(fud);
}