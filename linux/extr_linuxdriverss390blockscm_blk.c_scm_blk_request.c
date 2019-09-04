#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scm_request {TYPE_3__* aob; } ;
struct scm_queue {int /*<<< orphan*/  lock; struct scm_request* scmrq; } ;
struct scm_device {int /*<<< orphan*/  dev; } ;
struct scm_blk_dev {int dummy; } ;
struct request {int dummy; } ;
struct blk_mq_queue_data {scalar_t__ last; struct request* rq; } ;
struct blk_mq_hw_ctx {struct scm_queue* driver_data; TYPE_1__* queue; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_5__ {scalar_t__ msb_count; } ;
struct TYPE_6__ {TYPE_2__ request; } ;
struct TYPE_4__ {struct scm_device* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  SCM_LOG (int,char*) ; 
 int /*<<< orphan*/  blk_mq_start_request (struct request*) ; 
 struct scm_blk_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ nr_requests_per_io ; 
 int /*<<< orphan*/  scm_permit_request (struct scm_blk_dev*,struct request*) ; 
 struct scm_request* scm_request_fetch () ; 
 int /*<<< orphan*/  scm_request_init (struct scm_blk_dev*,struct scm_request*) ; 
 scalar_t__ scm_request_prepare (struct scm_request*) ; 
 int /*<<< orphan*/  scm_request_set (struct scm_request*,struct request*) ; 
 int /*<<< orphan*/  scm_request_start (struct scm_request*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static blk_status_t scm_blk_request(struct blk_mq_hw_ctx *hctx,
			   const struct blk_mq_queue_data *qd)
{
	struct scm_device *scmdev = hctx->queue->queuedata;
	struct scm_blk_dev *bdev = dev_get_drvdata(&scmdev->dev);
	struct scm_queue *sq = hctx->driver_data;
	struct request *req = qd->rq;
	struct scm_request *scmrq;

	spin_lock(&sq->lock);
	if (!scm_permit_request(bdev, req)) {
		spin_unlock(&sq->lock);
		return BLK_STS_RESOURCE;
	}

	scmrq = sq->scmrq;
	if (!scmrq) {
		scmrq = scm_request_fetch();
		if (!scmrq) {
			SCM_LOG(5, "no request");
			spin_unlock(&sq->lock);
			return BLK_STS_RESOURCE;
		}
		scm_request_init(bdev, scmrq);
		sq->scmrq = scmrq;
	}
	scm_request_set(scmrq, req);

	if (scm_request_prepare(scmrq)) {
		SCM_LOG(5, "aidaw alloc failed");
		scm_request_set(scmrq, NULL);

		if (scmrq->aob->request.msb_count)
			scm_request_start(scmrq);

		sq->scmrq = NULL;
		spin_unlock(&sq->lock);
		return BLK_STS_RESOURCE;
	}
	blk_mq_start_request(req);

	if (qd->last || scmrq->aob->request.msb_count == nr_requests_per_io) {
		scm_request_start(scmrq);
		sq->scmrq = NULL;
	}
	spin_unlock(&sq->lock);
	return BLK_STS_OK;
}