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
struct linger_work {int /*<<< orphan*/  work; int /*<<< orphan*/  pending_item; int /*<<< orphan*/  queued_stamp; struct ceph_osd_linger_request* lreq; } ;
struct ceph_osd_linger_request {int /*<<< orphan*/  pending_lworks; struct ceph_osd_client* osdc; } ;
struct ceph_osd_client {int /*<<< orphan*/  notify_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_lreq_locked (struct ceph_osd_linger_request*) ; 

__attribute__((used)) static void lwork_queue(struct linger_work *lwork)
{
	struct ceph_osd_linger_request *lreq = lwork->lreq;
	struct ceph_osd_client *osdc = lreq->osdc;

	verify_lreq_locked(lreq);
	WARN_ON(!list_empty(&lwork->pending_item));

	lwork->queued_stamp = jiffies;
	list_add_tail(&lwork->pending_item, &lreq->pending_lworks);
	queue_work(osdc->notify_wq, &lwork->work);
}