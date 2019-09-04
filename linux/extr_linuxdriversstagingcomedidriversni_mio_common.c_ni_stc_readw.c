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
struct ni_private {int /*<<< orphan*/  window_lock; int /*<<< orphan*/  mite; scalar_t__ is_m_series; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  NI_E_STC_WINDOW_ADDR_REG ; 
 int NI_E_STC_WINDOW_DATA_REG ; 
 unsigned int m_series_stc_read (struct comedi_device*,int) ; 
 unsigned int ni_readw (struct comedi_device*,int) ; 
 int /*<<< orphan*/  ni_writew (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int ni_stc_readw(struct comedi_device *dev, int reg)
{
	struct ni_private *devpriv = dev->private;
	unsigned long flags;
	unsigned int val;

	if (devpriv->is_m_series) {
		val = m_series_stc_read(dev, reg);
	} else {
		spin_lock_irqsave(&devpriv->window_lock, flags);
		if (!devpriv->mite && reg < 8) {
			val = ni_readw(dev, reg * 2);
		} else {
			ni_writew(dev, reg, NI_E_STC_WINDOW_ADDR_REG);
			val = ni_readw(dev, NI_E_STC_WINDOW_DATA_REG);
		}
		spin_unlock_irqrestore(&devpriv->window_lock, flags);
	}
	return val;
}