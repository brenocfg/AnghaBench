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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int PCXHR_CVR_HI08_HC ; 
 int /*<<< orphan*/  PCXHR_DSP_CVR ; 
 int /*<<< orphan*/  PCXHR_DSP_ICR ; 
 unsigned char PCXHR_ICR_HI08_HDRQ ; 
 unsigned char PCXHR_ICR_HI08_HF0 ; 
 unsigned char PCXHR_ICR_HI08_HF1 ; 
 unsigned char PCXHR_ICR_HI08_RREQ ; 
 unsigned char PCXHR_ICR_HI08_TREQ ; 
 unsigned int PCXHR_INPL (struct pcxhr_mgr*,int /*<<< orphan*/ ) ; 
 unsigned int PCXHR_MASK_EXTRA_INFO ; 
 unsigned int PCXHR_MASK_IT_HF0 ; 
 unsigned int PCXHR_MASK_IT_HF1 ; 
 unsigned int PCXHR_MASK_IT_MANAGE_HF5 ; 
 unsigned int PCXHR_MASK_IT_NO_HF0_HF1 ; 
 unsigned int PCXHR_MASK_IT_WAIT ; 
 unsigned int PCXHR_MASK_IT_WAIT_EXTRA ; 
 unsigned int PCXHR_MBOX0_HF5 ; 
 int /*<<< orphan*/  PCXHR_OUTPB (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  PCXHR_OUTPL (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PCXHR_PLX_MBOX0 ; 
 int /*<<< orphan*/  PCXHR_TIMEOUT_DSP ; 
 int /*<<< orphan*/  PCXHR_WAIT_IT ; 
 int /*<<< orphan*/  PCXHR_WAIT_IT_EXTRA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int pcxhr_check_reg_bit (struct pcxhr_mgr*,int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static int pcxhr_send_it_dsp(struct pcxhr_mgr *mgr,
			     unsigned int itdsp, int atomic)
{
	int err;
	unsigned char reg;

	if (itdsp & PCXHR_MASK_IT_MANAGE_HF5) {
		/* clear hf5 bit */
		PCXHR_OUTPL(mgr, PCXHR_PLX_MBOX0,
			    PCXHR_INPL(mgr, PCXHR_PLX_MBOX0) &
			    ~PCXHR_MBOX0_HF5);
	}
	if ((itdsp & PCXHR_MASK_IT_NO_HF0_HF1) == 0) {
		reg = (PCXHR_ICR_HI08_RREQ |
		       PCXHR_ICR_HI08_TREQ |
		       PCXHR_ICR_HI08_HDRQ);
		if (itdsp & PCXHR_MASK_IT_HF0)
			reg |= PCXHR_ICR_HI08_HF0;
		if (itdsp & PCXHR_MASK_IT_HF1)
			reg |= PCXHR_ICR_HI08_HF1;
		PCXHR_OUTPB(mgr, PCXHR_DSP_ICR, reg);
	}
	reg = (unsigned char)(((itdsp & PCXHR_MASK_EXTRA_INFO) >> 1) |
			      PCXHR_CVR_HI08_HC);
	PCXHR_OUTPB(mgr, PCXHR_DSP_CVR, reg);
	if (itdsp & PCXHR_MASK_IT_WAIT) {
		if (atomic)
			mdelay(PCXHR_WAIT_IT);
		else
			msleep(PCXHR_WAIT_IT);
	}
	if (itdsp & PCXHR_MASK_IT_WAIT_EXTRA) {
		if (atomic)
			mdelay(PCXHR_WAIT_IT_EXTRA);
		else
			msleep(PCXHR_WAIT_IT);
	}
	/* wait for CVR_HI08_HC == 0 */
	err = pcxhr_check_reg_bit(mgr, PCXHR_DSP_CVR,  PCXHR_CVR_HI08_HC, 0,
				  PCXHR_TIMEOUT_DSP, &reg);
	if (err) {
		dev_err(&mgr->pci->dev, "pcxhr_send_it_dsp : TIMEOUT CVR\n");
		return err;
	}
	if (itdsp & PCXHR_MASK_IT_MANAGE_HF5) {
		/* wait for hf5 bit */
		err = pcxhr_check_reg_bit(mgr, PCXHR_PLX_MBOX0,
					  PCXHR_MBOX0_HF5,
					  PCXHR_MBOX0_HF5,
					  PCXHR_TIMEOUT_DSP,
					  &reg);
		if (err) {
			dev_err(&mgr->pci->dev,
				   "pcxhr_send_it_dsp : TIMEOUT HF5\n");
			return err;
		}
	}
	return 0; /* retry not handled here */
}