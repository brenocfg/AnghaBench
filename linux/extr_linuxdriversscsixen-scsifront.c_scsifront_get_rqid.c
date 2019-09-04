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
struct vscsifrnt_info {int /*<<< orphan*/  shadow_lock; int /*<<< orphan*/  shadow_free_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSCSIIF_MAX_REQS ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int scsifront_get_rqid(struct vscsifrnt_info *info)
{
	unsigned long flags;
	int free;

	spin_lock_irqsave(&info->shadow_lock, flags);

	free = find_first_bit(info->shadow_free_bitmap, VSCSIIF_MAX_REQS);
	__clear_bit(free, info->shadow_free_bitmap);

	spin_unlock_irqrestore(&info->shadow_lock, flags);

	return free;
}