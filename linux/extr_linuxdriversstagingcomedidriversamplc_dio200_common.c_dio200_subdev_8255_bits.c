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
struct dio200_subdev_8255 {scalar_t__ ofs; } ;
struct comedi_subdevice {int state; struct dio200_subdev_8255* private; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ I8255_DATA_A_REG ; 
 scalar_t__ I8255_DATA_B_REG ; 
 scalar_t__ I8255_DATA_C_REG ; 
 unsigned int comedi_dio_update_state (struct comedi_subdevice*,unsigned int*) ; 
 int dio200_read8 (struct comedi_device*,scalar_t__) ; 
 int /*<<< orphan*/  dio200_write8 (struct comedi_device*,scalar_t__,int) ; 

__attribute__((used)) static int dio200_subdev_8255_bits(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	struct dio200_subdev_8255 *subpriv = s->private;
	unsigned int mask;
	unsigned int val;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		if (mask & 0xff) {
			dio200_write8(dev, subpriv->ofs + I8255_DATA_A_REG,
				      s->state & 0xff);
		}
		if (mask & 0xff00) {
			dio200_write8(dev, subpriv->ofs + I8255_DATA_B_REG,
				      (s->state >> 8) & 0xff);
		}
		if (mask & 0xff0000) {
			dio200_write8(dev, subpriv->ofs + I8255_DATA_C_REG,
				      (s->state >> 16) & 0xff);
		}
	}

	val = dio200_read8(dev, subpriv->ofs + I8255_DATA_A_REG);
	val |= dio200_read8(dev, subpriv->ofs + I8255_DATA_B_REG) << 8;
	val |= dio200_read8(dev, subpriv->ofs + I8255_DATA_C_REG) << 16;

	data[1] = val;

	return insn->n;
}