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
struct intel8x0 {unsigned int codec_isr_bits; unsigned int* codec_bit; size_t* ac97_sdin; TYPE_1__* card; scalar_t__ buggy_semaphore; scalar_t__ in_sdin_init; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_SEMA ; 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  GLOB_STA ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 int ICH_CAS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  iagetword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int igetbyte (struct intel8x0*,int /*<<< orphan*/ ) ; 
 unsigned int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_intel8x0_codec_semaphore(struct intel8x0 *chip, unsigned int codec)
{
	int time;
	
	if (codec > 2)
		return -EIO;
	if (chip->in_sdin_init) {
		/* we don't know the ready bit assignment at the moment */
		/* so we check any */
		codec = chip->codec_isr_bits;
	} else {
		codec = chip->codec_bit[chip->ac97_sdin[codec]];
	}

	/* codec ready ? */
	if ((igetdword(chip, ICHREG(GLOB_STA)) & codec) == 0)
		return -EIO;

	if (chip->buggy_semaphore)
		return 0; /* just ignore ... */

	/* Anyone holding a semaphore for 1 msec should be shot... */
	time = 100;
      	do {
      		if (!(igetbyte(chip, ICHREG(ACC_SEMA)) & ICH_CAS))
      			return 0;
		udelay(10);
	} while (time--);

	/* access to some forbidden (non existent) ac97 registers will not
	 * reset the semaphore. So even if you don't get the semaphore, still
	 * continue the access. We don't need the semaphore anyway. */
	dev_err(chip->card->dev,
		"codec_semaphore: semaphore is not ready [0x%x][0x%x]\n",
			igetbyte(chip, ICHREG(ACC_SEMA)), igetdword(chip, ICHREG(GLOB_STA)));
	iagetword(chip, 0);	/* clear semaphore flag */
	/* I don't care about the semaphore */
	return -EBUSY;
}