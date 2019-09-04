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
struct labpc_private {int cmd2; int cmd3; int /*<<< orphan*/  (* write_byte ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; struct labpc_private* private; } ;

/* Variables and functions */
 int CMD2_HWTRIG ; 
 int CMD2_PRETRIG ; 
 int /*<<< orphan*/  CMD2_REG ; 
 int CMD2_SWTRIG ; 
 int /*<<< orphan*/  CMD3_REG ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int labpc_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct labpc_private *devpriv = dev->private;
	unsigned long flags;

	spin_lock_irqsave(&dev->spinlock, flags);
	devpriv->cmd2 &= ~(CMD2_SWTRIG | CMD2_HWTRIG | CMD2_PRETRIG);
	devpriv->write_byte(dev, devpriv->cmd2, CMD2_REG);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	devpriv->cmd3 = 0;
	devpriv->write_byte(dev, devpriv->cmd3, CMD3_REG);

	return 0;
}