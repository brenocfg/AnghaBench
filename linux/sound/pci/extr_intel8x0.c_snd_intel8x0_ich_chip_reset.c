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
struct intel8x0 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GLOB_CNT ; 
 int HZ ; 
 int /*<<< orphan*/  ICHREG (int /*<<< orphan*/ ) ; 
 unsigned int ICH_AC97COLD ; 
 unsigned int ICH_AC97WARM ; 
 unsigned int ICH_ACLINK ; 
 unsigned int ICH_PCM_246_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int igetdword (struct intel8x0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iputdword (struct intel8x0*,int /*<<< orphan*/ ,unsigned int) ; 
 int jiffies ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_after_eq (unsigned long,int) ; 

__attribute__((used)) static int snd_intel8x0_ich_chip_reset(struct intel8x0 *chip)
{
	unsigned long end_time;
	unsigned int cnt;
	/* ACLink on, 2 channels */
	cnt = igetdword(chip, ICHREG(GLOB_CNT));
	cnt &= ~(ICH_ACLINK | ICH_PCM_246_MASK);
	/* finish cold or do warm reset */
	cnt |= (cnt & ICH_AC97COLD) == 0 ? ICH_AC97COLD : ICH_AC97WARM;
	iputdword(chip, ICHREG(GLOB_CNT), cnt);
	end_time = (jiffies + (HZ / 4)) + 1;
	do {
		if ((igetdword(chip, ICHREG(GLOB_CNT)) & ICH_AC97WARM) == 0)
			return 0;
		schedule_timeout_uninterruptible(1);
	} while (time_after_eq(end_time, jiffies));
	dev_err(chip->card->dev, "AC'97 warm reset still in progress? [0x%x]\n",
		   igetdword(chip, ICHREG(GLOB_CNT)));
	return -EIO;
}