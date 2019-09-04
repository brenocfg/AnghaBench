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
struct mgsl_struct {int idle_mode; int /*<<< orphan*/  irq_spinlock; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usc_set_txidle (struct mgsl_struct*) ; 

__attribute__((used)) static int mgsl_set_txidle(struct mgsl_struct * info, int idle_mode)
{
 	unsigned long flags;
 
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_set_txidle(%s,%d)\n", __FILE__,__LINE__,
			info->device_name, idle_mode );
			
	spin_lock_irqsave(&info->irq_spinlock,flags);
	info->idle_mode = idle_mode;
	usc_set_txidle( info );
	spin_unlock_irqrestore(&info->irq_spinlock,flags);
	return 0;
	
}