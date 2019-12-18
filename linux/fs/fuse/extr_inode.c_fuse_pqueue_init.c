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
struct fuse_pqueue {int connected; int /*<<< orphan*/  io; int /*<<< orphan*/ * processing; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int FUSE_PQ_HASH_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_pqueue_init(struct fuse_pqueue *fpq)
{
	unsigned int i;

	spin_lock_init(&fpq->lock);
	for (i = 0; i < FUSE_PQ_HASH_SIZE; i++)
		INIT_LIST_HEAD(&fpq->processing[i]);
	INIT_LIST_HEAD(&fpq->io);
	fpq->connected = 1;
}