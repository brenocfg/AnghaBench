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
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 unsigned int AREF_DIFF ; 
 unsigned int CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ ICP_MULTI_ADC_CSR ; 
 unsigned int ICP_MULTI_ADC_CSR_DI ; 
 unsigned int ICP_MULTI_ADC_CSR_DI_CHAN (unsigned int) ; 
 unsigned int ICP_MULTI_ADC_CSR_SE_CHAN (unsigned int) ; 
 unsigned int ICP_MULTI_ADC_CSR_ST ; 
 scalar_t__ ICP_MULTI_AI ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icp_multi_ai_eoc ; 
 unsigned int* range_codes_analog ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static int icp_multi_ai_insn_read(struct comedi_device *dev,
				  struct comedi_subdevice *s,
				  struct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	unsigned int range = CR_RANGE(insn->chanspec);
	unsigned int aref = CR_AREF(insn->chanspec);
	unsigned int adc_csr;
	int ret = 0;
	int n;

	/* Set mode and range data for specified channel */
	if (aref == AREF_DIFF) {
		adc_csr = ICP_MULTI_ADC_CSR_DI_CHAN(chan) |
			  ICP_MULTI_ADC_CSR_DI;
	} else {
		adc_csr = ICP_MULTI_ADC_CSR_SE_CHAN(chan);
	}
	adc_csr |= range_codes_analog[range];
	writew(adc_csr, dev->mmio + ICP_MULTI_ADC_CSR);

	for (n = 0; n < insn->n; n++) {
		/*  Set start ADC bit */
		writew(adc_csr | ICP_MULTI_ADC_CSR_ST,
		       dev->mmio + ICP_MULTI_ADC_CSR);

		udelay(1);

		/*  Wait for conversion to complete, or get fed up waiting */
		ret = comedi_timeout(dev, s, insn, icp_multi_ai_eoc, 0);
		if (ret)
			break;

		data[n] = (readw(dev->mmio + ICP_MULTI_AI) >> 4) & 0x0fff;
	}

	return ret ? ret : n;
}