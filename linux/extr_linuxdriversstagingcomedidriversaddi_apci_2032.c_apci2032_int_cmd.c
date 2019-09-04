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
struct comedi_subdevice {struct apci2032_int_private* private; TYPE_1__* async; } ;
struct comedi_device {scalar_t__ iobase; } ;
struct comedi_cmd {unsigned int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
struct apci2032_int_private {unsigned char enabled_isns; int active; int /*<<< orphan*/  spinlock; } ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ APCI2032_INT_CTRL_REG ; 
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int apci2032_int_cmd(struct comedi_device *dev,
			    struct comedi_subdevice *s)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	struct apci2032_int_private *subpriv = s->private;
	unsigned char enabled_isns;
	unsigned int n;
	unsigned long flags;

	enabled_isns = 0;
	for (n = 0; n < cmd->chanlist_len; n++)
		enabled_isns |= 1 << CR_CHAN(cmd->chanlist[n]);

	spin_lock_irqsave(&subpriv->spinlock, flags);

	subpriv->enabled_isns = enabled_isns;
	subpriv->active = true;
	outl(enabled_isns, dev->iobase + APCI2032_INT_CTRL_REG);

	spin_unlock_irqrestore(&subpriv->spinlock, flags);

	return 0;
}