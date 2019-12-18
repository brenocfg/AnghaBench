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
struct list_head {int dummy; } ;
struct TYPE_2__ {struct list_head* processing; } ;
struct fuse_dev {TYPE_1__ pq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_PQ_HASH_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fuse_pqueue_init (TYPE_1__*) ; 
 struct list_head* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fuse_dev*) ; 
 struct fuse_dev* kzalloc (int,int /*<<< orphan*/ ) ; 

struct fuse_dev *fuse_dev_alloc(void)
{
	struct fuse_dev *fud;
	struct list_head *pq;

	fud = kzalloc(sizeof(struct fuse_dev), GFP_KERNEL);
	if (!fud)
		return NULL;

	pq = kcalloc(FUSE_PQ_HASH_SIZE, sizeof(struct list_head), GFP_KERNEL);
	if (!pq) {
		kfree(fud);
		return NULL;
	}

	fud->pq.processing = pq;
	fuse_pqueue_init(&fud->pq);

	return fud;
}