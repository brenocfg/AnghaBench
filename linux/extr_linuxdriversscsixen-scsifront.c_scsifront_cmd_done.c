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
struct vscsifrnt_info {int /*<<< orphan*/  wq_sync; TYPE_1__* host; scalar_t__ wait_ring_available; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int scsifront_ring_drain (struct vscsifrnt_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scsifront_cmd_done(struct vscsifrnt_info *info)
{
	int more_to_do;
	unsigned long flags;

	spin_lock_irqsave(info->host->host_lock, flags);

	more_to_do = scsifront_ring_drain(info);

	info->wait_ring_available = 0;

	spin_unlock_irqrestore(info->host->host_lock, flags);

	wake_up(&info->wq_sync);

	return more_to_do;
}