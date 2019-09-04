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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ NI6527_DI_REG (int) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static int ni6527_di_insn_bits(struct comedi_device *dev,
			       struct comedi_subdevice *s,
			       struct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int val;

	val = readb(dev->mmio + NI6527_DI_REG(0));
	val |= (readb(dev->mmio + NI6527_DI_REG(1)) << 8);
	val |= (readb(dev->mmio + NI6527_DI_REG(2)) << 16);

	data[1] = val;

	return insn->n;
}