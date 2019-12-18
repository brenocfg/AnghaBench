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
struct linger_work {int /*<<< orphan*/  pending_item; struct ceph_osd_linger_request* lreq; } ;
struct ceph_osd_linger_request {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct linger_work*) ; 
 int /*<<< orphan*/  linger_put (struct ceph_osd_linger_request*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lwork_free(struct linger_work *lwork)
{
	struct ceph_osd_linger_request *lreq = lwork->lreq;

	mutex_lock(&lreq->lock);
	list_del(&lwork->pending_item);
	mutex_unlock(&lreq->lock);

	linger_put(lreq);
	kfree(lwork);
}