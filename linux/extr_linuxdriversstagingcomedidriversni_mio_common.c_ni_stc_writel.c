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
 int /*<<< orphan*/  m_series_stc_write (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned int,int) ; 

__attribute__((used)) static void ni_stc_writel(struct comedi_device *dev,
			  unsigned int data, int reg)
{
	struct ni_private *devpriv = dev->private;

	if (devpriv->is_m_series) {
		m_series_stc_write(dev, data, reg);
	} else {
		ni_stc_writew(dev, data >> 16, reg);
		ni_stc_writew(dev, data & 0xffff, reg + 1);
	}
}