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
typedef  unsigned int u16 ;
struct dyna_pci10xx_private {int /*<<< orphan*/  mutex; int /*<<< orphan*/  BADR3; } ;
struct comedi_subdevice {unsigned int state; } ;
struct comedi_insn {int n; } ;
struct comedi_device {struct dyna_pci10xx_private* private; } ;

/* Variables and functions */
 unsigned int inw_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int dyna_pci10xx_di_insn_bits(struct comedi_device *dev,
				     struct comedi_subdevice *s,
				     struct comedi_insn *insn,
				     unsigned int *data)
{
	struct dyna_pci10xx_private *devpriv = dev->private;
	u16 d = 0;

	mutex_lock(&devpriv->mutex);
	smp_mb();
	d = inw_p(devpriv->BADR3);
	usleep_range(10, 100);

	/* on return the data[0] contains output and data[1] contains input */
	data[1] = d;
	data[0] = s->state;
	mutex_unlock(&devpriv->mutex);
	return insn->n;
}