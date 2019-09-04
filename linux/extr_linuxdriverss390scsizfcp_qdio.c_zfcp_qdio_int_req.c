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
struct zfcp_qdio {int /*<<< orphan*/  req_q_wq; int /*<<< orphan*/  req_q_free; int /*<<< orphan*/  stat_lock; int /*<<< orphan*/  req_q; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (unsigned int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_qdio_account (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  zfcp_qdio_handler_error (struct zfcp_qdio*,char*,unsigned int) ; 
 int /*<<< orphan*/  zfcp_qdio_zero_sbals (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void zfcp_qdio_int_req(struct ccw_device *cdev, unsigned int qdio_err,
			      int queue_no, int idx, int count,
			      unsigned long parm)
{
	struct zfcp_qdio *qdio = (struct zfcp_qdio *) parm;

	if (unlikely(qdio_err)) {
		zfcp_qdio_handler_error(qdio, "qdireq1", qdio_err);
		return;
	}

	/* cleanup all SBALs being program-owned now */
	zfcp_qdio_zero_sbals(qdio->req_q, idx, count);

	spin_lock_irq(&qdio->stat_lock);
	zfcp_qdio_account(qdio);
	spin_unlock_irq(&qdio->stat_lock);
	atomic_add(count, &qdio->req_q_free);
	wake_up(&qdio->req_q_wq);
}