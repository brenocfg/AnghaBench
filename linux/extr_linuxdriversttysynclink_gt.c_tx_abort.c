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
struct slgt_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tdma_reset (struct slgt_info*) ; 

__attribute__((used)) static int tx_abort(struct slgt_info *info)
{
 	unsigned long flags;
	DBGINFO(("%s tx_abort\n", info->device_name));
	spin_lock_irqsave(&info->lock,flags);
	tdma_reset(info);
	spin_unlock_irqrestore(&info->lock,flags);
	return 0;
}