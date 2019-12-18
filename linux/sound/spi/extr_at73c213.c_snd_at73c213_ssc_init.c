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
struct snd_at73c213 {TYPE_1__* ssc; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int SSC_BF (int /*<<< orphan*/ ,int) ; 
 int SSC_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCMR ; 
 int /*<<< orphan*/  TCMR_CKO ; 
 int /*<<< orphan*/  TCMR_PERIOD ; 
 int /*<<< orphan*/  TCMR_START ; 
 int /*<<< orphan*/  TCMR_STTDLY ; 
 int /*<<< orphan*/  TFMR ; 
 int /*<<< orphan*/  TFMR_DATLEN ; 
 int /*<<< orphan*/  TFMR_DATNB ; 
 int /*<<< orphan*/  TFMR_FSLEN ; 
 int /*<<< orphan*/  TFMR_FSOS ; 
 int /*<<< orphan*/  TFMR_MSBF ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_at73c213_ssc_init(struct snd_at73c213 *chip)
{
	/*
	 * Continuous clock output.
	 * Starts on falling TF.
	 * Delay 1 cycle (1 bit).
	 * Periode is 16 bit (16 - 1).
	 */
	ssc_writel(chip->ssc->regs, TCMR,
			SSC_BF(TCMR_CKO, 1)
			| SSC_BF(TCMR_START, 4)
			| SSC_BF(TCMR_STTDLY, 1)
			| SSC_BF(TCMR_PERIOD, 16 - 1));
	/*
	 * Data length is 16 bit (16 - 1).
	 * Transmit MSB first.
	 * Transmit 2 words each transfer.
	 * Frame sync length is 16 bit (16 - 1).
	 * Frame starts on negative pulse.
	 */
	ssc_writel(chip->ssc->regs, TFMR,
			SSC_BF(TFMR_DATLEN, 16 - 1)
			| SSC_BIT(TFMR_MSBF)
			| SSC_BF(TFMR_DATNB, 1)
			| SSC_BF(TFMR_FSLEN, 16 - 1)
			| SSC_BF(TFMR_FSOS, 1));

	return 0;
}