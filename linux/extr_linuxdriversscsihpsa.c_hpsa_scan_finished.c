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
struct ctlr_info {int scan_finished; int /*<<< orphan*/  scan_lock; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct ctlr_info* shost_to_hba (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hpsa_scan_finished(struct Scsi_Host *sh,
	unsigned long elapsed_time)
{
	struct ctlr_info *h = shost_to_hba(sh);
	unsigned long flags;
	int finished;

	spin_lock_irqsave(&h->scan_lock, flags);
	finished = h->scan_finished;
	spin_unlock_irqrestore(&h->scan_lock, flags);
	return finished;
}