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
struct inode {int dummy; } ;
struct fuse_pqueue {int /*<<< orphan*/  lock; int /*<<< orphan*/ * processing; int /*<<< orphan*/  io; } ;
struct fuse_dev {struct fuse_pqueue pq; struct fuse_conn* fc; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fasync; } ;
struct fuse_conn {TYPE_1__ iq; int /*<<< orphan*/  dev_count; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int FUSE_PQ_HASH_SIZE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_requests (struct fuse_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_abort_conn (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_dev_free (struct fuse_dev*) ; 
 struct fuse_dev* fuse_get_dev (struct file*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_end ; 

int fuse_dev_release(struct inode *inode, struct file *file)
{
	struct fuse_dev *fud = fuse_get_dev(file);

	if (fud) {
		struct fuse_conn *fc = fud->fc;
		struct fuse_pqueue *fpq = &fud->pq;
		LIST_HEAD(to_end);
		unsigned int i;

		spin_lock(&fpq->lock);
		WARN_ON(!list_empty(&fpq->io));
		for (i = 0; i < FUSE_PQ_HASH_SIZE; i++)
			list_splice_init(&fpq->processing[i], &to_end);
		spin_unlock(&fpq->lock);

		end_requests(fc, &to_end);

		/* Are we the last open device? */
		if (atomic_dec_and_test(&fc->dev_count)) {
			WARN_ON(fc->iq.fasync != NULL);
			fuse_abort_conn(fc);
		}
		fuse_dev_free(fud);
	}
	return 0;
}