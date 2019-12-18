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
struct intel8x0 {scalar_t__ device_type; unsigned int codec_isr_bits; int ncodecs; unsigned int* codec_bit; size_t* ac97_sdin; int /*<<< orphan*/  pci; scalar_t__* ac97; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DEVICE_NFORCE ; 
 scalar_t__ DEVICE_SIS ; 
 int EIO ; 
 int /*<<< orphan*/  GLOB_STA ; 
 int HZ ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 unsigned int ICH_MCINT ; 
 unsigned int ICH_NVSPINT ; 
 unsigned int ICH_PIINT ; 
 unsigned int ICH_POINT ; 
 unsigned int ICH_RCS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int igetword (struct intel8x0*,int) ; 
 int /*<<< orphan*/  iputdword (struct intel8x0*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  iputword (struct intel8x0*,int,int) ; 
 int jiffies ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ snd_intel8x0_ich_chip_can_cold_reset (struct intel8x0*) ; 
 int snd_intel8x0_ich_chip_cold_reset (struct intel8x0*) ; 
 int snd_intel8x0_ich_chip_reset (struct intel8x0*) ; 
 int /*<<< orphan*/  spdif_aclink ; 
 scalar_t__ time_after_eq (unsigned long,int) ; 

__attribute__((used)) static int snd_intel8x0_ich_chip_init(struct intel8x0 *chip, int probing)
{
	unsigned long end_time;
	unsigned int status, nstatus;
	unsigned int cnt;
	int err;

	/* put logic to right state */
	/* first clear status bits */
	status = ICH_RCS | ICH_MCINT | ICH_POINT | ICH_PIINT;
	if (chip->device_type == DEVICE_NFORCE)
		status |= ICH_NVSPINT;
	cnt = igetdword(chip, ICHREG(GLOB_STA));
	iputdword(chip, ICHREG(GLOB_STA), cnt & status);

	if (snd_intel8x0_ich_chip_can_cold_reset(chip))
		err = snd_intel8x0_ich_chip_cold_reset(chip);
	else
		err = snd_intel8x0_ich_chip_reset(chip);
	if (err < 0)
		return err;

	if (probing) {
		/* wait for any codec ready status.
		 * Once it becomes ready it should remain ready
		 * as long as we do not disable the ac97 link.
		 */
		end_time = jiffies + HZ;
		do {
			status = igetdword(chip, ICHREG(GLOB_STA)) &
				chip->codec_isr_bits;
			if (status)
				break;
			schedule_timeout_uninterruptible(1);
		} while (time_after_eq(end_time, jiffies));
		if (! status) {
			/* no codec is found */
			dev_err(chip->card->dev,
				"codec_ready: codec is not ready [0x%x]\n",
				   igetdword(chip, ICHREG(GLOB_STA)));
			return -EIO;
		}

		/* wait for other codecs ready status. */
		end_time = jiffies + HZ / 4;
		while (status != chip->codec_isr_bits &&
		       time_after_eq(end_time, jiffies)) {
			schedule_timeout_uninterruptible(1);
			status |= igetdword(chip, ICHREG(GLOB_STA)) &
				chip->codec_isr_bits;
		}

	} else {
		/* resume phase */
		int i;
		status = 0;
		for (i = 0; i < chip->ncodecs; i++)
			if (chip->ac97[i])
				status |= chip->codec_bit[chip->ac97_sdin[i]];
		/* wait until all the probed codecs are ready */
		end_time = jiffies + HZ;
		do {
			nstatus = igetdword(chip, ICHREG(GLOB_STA)) &
				chip->codec_isr_bits;
			if (status == nstatus)
				break;
			schedule_timeout_uninterruptible(1);
		} while (time_after_eq(end_time, jiffies));
	}

	if (chip->device_type == DEVICE_SIS) {
		/* unmute the output on SIS7012 */
		iputword(chip, 0x4c, igetword(chip, 0x4c) | 1);
	}
	if (chip->device_type == DEVICE_NFORCE && !spdif_aclink) {
		/* enable SPDIF interrupt */
		unsigned int val;
		pci_read_config_dword(chip->pci, 0x4c, &val);
		val |= 0x1000000;
		pci_write_config_dword(chip->pci, 0x4c, val);
	}
      	return 0;
}