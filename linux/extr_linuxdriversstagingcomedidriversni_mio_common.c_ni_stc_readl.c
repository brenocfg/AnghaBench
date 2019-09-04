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
struct ni_private {scalar_t__ is_m_series; } ;
struct comedi_device {struct ni_private* private; } ;

/* Variables and functions */
 unsigned int m_series_stc_read (struct comedi_device*,int) ; 
 unsigned int ni_stc_readw (struct comedi_device*,int) ; 

__attribute__((used)) static unsigned int ni_stc_readl(struct comedi_device *dev, int reg)
{
	struct ni_private *devpriv = dev->private;
	unsigned int val;

	if (devpriv->is_m_series) {
		val = m_series_stc_read(dev, reg);
	} else {
		val = ni_stc_readw(dev, reg) << 16;
		val |= ni_stc_readw(dev, reg + 1);
	}
	return val;
}