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
struct comedi_insn {int dummy; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int S626_PSR_GPIO2 ; 
 scalar_t__ S626_P_PSR ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static int s626_ai_eoc(struct comedi_device *dev,
		       struct comedi_subdevice *s,
		       struct comedi_insn *insn,
		       unsigned long context)
{
	unsigned int status;

	status = readl(dev->mmio + S626_P_PSR);
	if (status & S626_PSR_GPIO2)
		return 0;
	return -EBUSY;
}