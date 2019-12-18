#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcxhr_mgr {TYPE_1__* pci; } ;
struct firmware {int size; unsigned char* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCXHR_DSP_ISR ; 
 int /*<<< orphan*/  PCXHR_DSP_TXH ; 
 int /*<<< orphan*/  PCXHR_DSP_TXL ; 
 int /*<<< orphan*/  PCXHR_DSP_TXM ; 
 int /*<<< orphan*/  PCXHR_ISR_HI08_TRDY ; 
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned char const) ; 
 int /*<<< orphan*/  PCXHR_TIMEOUT_DSP ; 
 int /*<<< orphan*/  PCXHR_WAIT_DEFAULT ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int pcxhr_check_reg_bit (struct pcxhr_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ snd_BUG_ON (int) ; 

__attribute__((used)) static int pcxhr_download_dsp(struct pcxhr_mgr *mgr, const struct firmware *dsp)
{
	int err;
	unsigned int i;
	unsigned int len;
	const unsigned char *data;
	unsigned char dummy;
	/* check the length of boot image */
	if (dsp->size <= 0)
		return -EINVAL;
	if (dsp->size % 3)
		return -EINVAL;
	if (snd_BUG_ON(!dsp->data))
		return -EINVAL;
	/* transfert data buffer from PC to DSP */
	for (i = 0; i < dsp->size; i += 3) {
		data = dsp->data + i;
		if (i == 0) {
			/* test data header consistency */
			len = (unsigned int)((data[0]<<16) +
					     (data[1]<<8) +
					     data[2]);
			if (len && (dsp->size != (len + 2) * 3))
				return -EINVAL;
		}
		/* wait DSP ready for new transfer */
		err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_ISR,
					  PCXHR_ISR_HI08_TRDY,
					  PCXHR_ISR_HI08_TRDY,
					  PCXHR_TIMEOUT_DSP, &dummy);
		if (err) {
			dev_err(&mgr->pci->dev,
				   "dsp loading error at position %d\n", i);
			return err;
		}
		/* send host data */
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXH, data[0]);
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXM, data[1]);
		PCXHR_OUTPB(mgr, PCXHR_DSP_TXL, data[2]);

		/* don't take too much time in this loop... */
		cond_resched();
	}
	/* give some time to boot the DSP */
	msleep(PCXHR_WAIT_DEFAULT);
	return 0;
}