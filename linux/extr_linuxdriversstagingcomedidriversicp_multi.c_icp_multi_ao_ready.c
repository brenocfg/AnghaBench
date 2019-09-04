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
 scalar_t__ ICP_MULTI_DAC_CSR ; 
 unsigned int ICP_MULTI_DAC_CSR_BSY ; 
 unsigned int readw (scalar_t__) ; 

__attribute__((used)) static int icp_multi_ao_ready(struct comedi_device *dev,
			      struct comedi_subdevice *s,
			      struct comedi_insn *insn,
			      unsigned long context)
{
	unsigned int status;

	status = readw(dev->mmio + ICP_MULTI_DAC_CSR);
	if ((status & ICP_MULTI_DAC_CSR_BSY) == 0)
		return 0;
	return -EBUSY;
}