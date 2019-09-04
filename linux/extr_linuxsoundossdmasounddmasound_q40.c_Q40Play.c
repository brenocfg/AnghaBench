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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int count; scalar_t__ rear_size; scalar_t__ block_size; int /*<<< orphan*/  syncing; scalar_t__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q40PlayNextFrame (int) ; 
 TYPE_2__ dmasound ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__ write_sq ; 

__attribute__((used)) static void Q40Play(void)
{
        unsigned long flags;

	if (write_sq.active || write_sq.count<=0 ) {
		/* There's already a frame loaded */
		return;
	}

	/* nothing in the queue */
	if (write_sq.count <= 1 && write_sq.rear_size < write_sq.block_size && !write_sq.syncing) {
	         /* hmmm, the only existing frame is not
		  * yet filled and we're not syncing?
		  */
	         return;
	}
	spin_lock_irqsave(&dmasound.lock, flags);
	Q40PlayNextFrame(1);
	spin_unlock_irqrestore(&dmasound.lock, flags);
}