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
typedef  int /*<<< orphan*/  u16 ;
struct tty_struct {int /*<<< orphan*/  name; struct mgsl_struct* driver_data; } ;
struct mgsl_struct {int /*<<< orphan*/  irq_spinlock; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int BIT7 ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int EINVAL ; 
 int /*<<< orphan*/  IOCR ; 
 scalar_t__ debug_level ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mgsl_break(struct tty_struct *tty, int break_state)
{
	struct mgsl_struct * info = tty->driver_data;
	unsigned long flags;
	
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_break(%s,%d)\n",
			 __FILE__,__LINE__, info->device_name, break_state);
			 
	if (mgsl_paranoia_check(info, tty->name, "mgsl_break"))
		return -EINVAL;

	spin_lock_irqsave(&info->irq_spinlock,flags);
 	if (break_state == -1)
		usc_OutReg(info,IOCR,(u16)(usc_InReg(info,IOCR) | BIT7));
	else 
		usc_OutReg(info,IOCR,(u16)(usc_InReg(info,IOCR) & ~BIT7));
	spin_unlock_irqrestore(&info->irq_spinlock,flags);
	return 0;
	
}