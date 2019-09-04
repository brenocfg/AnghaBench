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
 int CR_CHAN (int /*<<< orphan*/ ) ; 
 int CR_RANGE (int /*<<< orphan*/ ) ; 
 int DB2K_ACQ_CONTROL_ADC_PACER_DISABLE ; 
 int DB2K_ACQ_CONTROL_ADC_PACER_ENABLE ; 
 int DB2K_ACQ_CONTROL_RESET_CONFIG_PIPE ; 
 int DB2K_ACQ_CONTROL_RESET_RESULTS_FIFO ; 
 int DB2K_ACQ_CONTROL_RESET_SCAN_LIST_FIFO ; 
 int DB2K_ACQ_CONTROL_SEQ_START_SCAN_LIST ; 
 int DB2K_ACQ_CONTROL_SEQ_STOP_SCAN_LIST ; 
 int /*<<< orphan*/  DB2K_ACQ_STATUS_CONFIG_PIPE_FULL ; 
 int /*<<< orphan*/  DB2K_ACQ_STATUS_LOGIC_SCANNING ; 
 int /*<<< orphan*/  DB2K_ACQ_STATUS_RESULTS_FIFO_HAS_DATA ; 
 scalar_t__ DB2K_REG_ACQ_CONTROL ; 
 scalar_t__ DB2K_REG_ACQ_PACER_CLOCK_DIV_HIGH ; 
 scalar_t__ DB2K_REG_ACQ_PACER_CLOCK_DIV_LOW ; 
 scalar_t__ DB2K_REG_ACQ_RESULTS_FIFO ; 
 int comedi_timeout (struct comedi_device*,struct comedi_subdevice*,struct comedi_insn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db2k_ai_status ; 
 int /*<<< orphan*/  db2k_setup_sampling (struct comedi_device*,int,int) ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int db2k_ai_insn_read(struct comedi_device *dev,
			     struct comedi_subdevice *s,
			     struct comedi_insn *insn, unsigned int *data)
{
	int gain, chan;
	int ret;
	int i;

	writew(DB2K_ACQ_CONTROL_RESET_SCAN_LIST_FIFO |
	       DB2K_ACQ_CONTROL_RESET_RESULTS_FIFO |
	       DB2K_ACQ_CONTROL_RESET_CONFIG_PIPE,
	       dev->mmio + DB2K_REG_ACQ_CONTROL);

	/*
	 * If pacer clock is not set to some high value (> 10 us), we
	 * risk multiple samples to be put into the result FIFO.
	 */
	/* 1 second, should be long enough */
	writel(1000000, dev->mmio + DB2K_REG_ACQ_PACER_CLOCK_DIV_LOW);
	writew(0, dev->mmio + DB2K_REG_ACQ_PACER_CLOCK_DIV_HIGH);

	gain = CR_RANGE(insn->chanspec);
	chan = CR_CHAN(insn->chanspec);

	/*
	 * This doesn't look efficient.  I decided to take the conservative
	 * approach when I did the insn conversion.  Perhaps it would be
	 * better to have broken it completely, then someone would have been
	 * forced to fix it.  --ds
	 */
	for (i = 0; i < insn->n; i++) {
		db2k_setup_sampling(dev, chan, gain);
		/* Enable reading from the scanlist FIFO */
		writew(DB2K_ACQ_CONTROL_SEQ_START_SCAN_LIST,
		       dev->mmio + DB2K_REG_ACQ_CONTROL);

		ret = comedi_timeout(dev, s, insn, db2k_ai_status,
				     DB2K_ACQ_STATUS_CONFIG_PIPE_FULL);
		if (ret)
			return ret;

		writew(DB2K_ACQ_CONTROL_ADC_PACER_ENABLE,
		       dev->mmio + DB2K_REG_ACQ_CONTROL);

		ret = comedi_timeout(dev, s, insn, db2k_ai_status,
				     DB2K_ACQ_STATUS_LOGIC_SCANNING);
		if (ret)
			return ret;

		ret =
		comedi_timeout(dev, s, insn, db2k_ai_status,
			       DB2K_ACQ_STATUS_RESULTS_FIFO_HAS_DATA);
		if (ret)
			return ret;

		data[i] = readw(dev->mmio + DB2K_REG_ACQ_RESULTS_FIFO);
		writew(DB2K_ACQ_CONTROL_ADC_PACER_DISABLE,
		       dev->mmio + DB2K_REG_ACQ_CONTROL);
		writew(DB2K_ACQ_CONTROL_SEQ_STOP_SCAN_LIST,
		       dev->mmio + DB2K_REG_ACQ_CONTROL);
	}

	return i;
}