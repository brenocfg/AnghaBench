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
struct dasd_device {int /*<<< orphan*/  ref_count; int /*<<< orphan*/  mem_lock; int /*<<< orphan*/  erp_chunks; } ;
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_free_chunk (int /*<<< orphan*/ *,struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
dasd_free_erp_request(struct dasd_ccw_req *cqr, struct dasd_device * device)
{
	unsigned long flags;

	spin_lock_irqsave(&device->mem_lock, flags);
	dasd_free_chunk(&device->erp_chunks, cqr);
	spin_unlock_irqrestore(&device->mem_lock, flags);
	atomic_dec(&device->ref_count);
}