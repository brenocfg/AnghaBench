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
struct dasd_device {int /*<<< orphan*/  mem_lock; int /*<<< orphan*/  ccw_chunks; } ;
struct dasd_ccw_req {int /*<<< orphan*/  mem_chunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_free_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dasd_sfree_request(struct dasd_ccw_req *cqr, struct dasd_device *device)
{
	unsigned long flags;

	spin_lock_irqsave(&device->mem_lock, flags);
	dasd_free_chunk(&device->ccw_chunks, cqr->mem_chunk);
	spin_unlock_irqrestore(&device->mem_lock, flags);
	dasd_put_device(device);
}