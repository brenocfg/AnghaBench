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
struct snd_ac97 {int scaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_MID ; 
 int /*<<< orphan*/  AC97_REC_GAIN ; 
 int /*<<< orphan*/  AC97_RESET ; 
 int AC97_SCAP_DETECT_BY_VENDOR ; 
 int /*<<< orphan*/  AC97_VENDOR_ID1 ; 
 int /*<<< orphan*/  AC97_VENDOR_ID2 ; 
 int ENODEV ; 
 int jiffies ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int snd_ac97_read (struct snd_ac97*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_after_eq (unsigned long,int) ; 

__attribute__((used)) static int ac97_reset_wait(struct snd_ac97 *ac97, int timeout, int with_modem)
{
	unsigned long end_time;
	unsigned short val;

	end_time = jiffies + timeout;
	do {
		
		/* use preliminary reads to settle the communication */
		snd_ac97_read(ac97, AC97_RESET);
		snd_ac97_read(ac97, AC97_VENDOR_ID1);
		snd_ac97_read(ac97, AC97_VENDOR_ID2);
		/* modem? */
		if (with_modem) {
			val = snd_ac97_read(ac97, AC97_EXTENDED_MID);
			if (val != 0xffff && (val & 1) != 0)
				return 0;
		}
		if (ac97->scaps & AC97_SCAP_DETECT_BY_VENDOR) {
			/* probably only Xbox issue - all registers are read as zero */
			val = snd_ac97_read(ac97, AC97_VENDOR_ID1);
			if (val != 0 && val != 0xffff)
				return 0;
		} else {
			/* because the PCM or MASTER volume registers can be modified,
			 * the REC_GAIN register is used for tests
			 */
			/* test if we can write to the record gain volume register */
			snd_ac97_write_cache(ac97, AC97_REC_GAIN, 0x8a05);
			if ((snd_ac97_read(ac97, AC97_REC_GAIN) & 0x7fff) == 0x0a05)
				return 0;
		}
		schedule_timeout_uninterruptible(1);
	} while (time_after_eq(end_time, jiffies));
	return -ENODEV;
}