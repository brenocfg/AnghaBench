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
struct mapleq {TYPE_1__* recvbuf; struct maple_device* dev; int /*<<< orphan*/  list; } ;
struct maple_device {int /*<<< orphan*/  unit; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bufx; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mapleq*) ; 
 TYPE_1__* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mapleq* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_queue_cache ; 

__attribute__((used)) static struct mapleq *maple_allocq(struct maple_device *mdev)
{
	struct mapleq *mq;

	mq = kzalloc(sizeof(*mq), GFP_KERNEL);
	if (!mq)
		goto failed_nomem;

	INIT_LIST_HEAD(&mq->list);
	mq->dev = mdev;
	mq->recvbuf = kmem_cache_zalloc(maple_queue_cache, GFP_KERNEL);
	if (!mq->recvbuf)
		goto failed_p2;
	mq->recvbuf->buf = &((mq->recvbuf->bufx)[0]);

	return mq;

failed_p2:
	kfree(mq);
failed_nomem:
	dev_err(&mdev->dev, "could not allocate memory for device (%d, %d)\n",
		mdev->port, mdev->unit);
	return NULL;
}