#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iocb {scalar_t__ aio_rw_flags; scalar_t__ aio_nbytes; scalar_t__ aio_offset; scalar_t__ aio_buf; } ;
struct fsync_iocb {int datasync; int /*<<< orphan*/  work; TYPE_2__* file; } ;
struct TYPE_4__ {TYPE_1__* f_op; } ;
struct TYPE_3__ {int /*<<< orphan*/  fsync; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aio_fsync_work ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aio_fsync(struct fsync_iocb *req, const struct iocb *iocb,
		     bool datasync)
{
	if (unlikely(iocb->aio_buf || iocb->aio_offset || iocb->aio_nbytes ||
			iocb->aio_rw_flags))
		return -EINVAL;

	if (unlikely(!req->file->f_op->fsync))
		return -EINVAL;

	req->datasync = datasync;
	INIT_WORK(&req->work, aio_fsync_work);
	schedule_work(&req->work);
	return 0;
}