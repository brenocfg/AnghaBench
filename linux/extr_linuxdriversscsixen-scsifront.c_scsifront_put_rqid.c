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
typedef  int /*<<< orphan*/  uint32_t ;
struct vscsifrnt_info {int /*<<< orphan*/  shadow_lock; } ;

/* Variables and functions */
 int _scsifront_put_rqid (struct vscsifrnt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsifront_wake_up (struct vscsifrnt_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void scsifront_put_rqid(struct vscsifrnt_info *info, uint32_t id)
{
	unsigned long flags;
	int kick;

	spin_lock_irqsave(&info->shadow_lock, flags);
	kick = _scsifront_put_rqid(info, id);
	spin_unlock_irqrestore(&info->shadow_lock, flags);

	if (kick)
		scsifront_wake_up(info);
}