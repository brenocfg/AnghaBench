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
struct snd_ac97 {int dummy; } ;
struct au1xpsc_audio_data {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CDC (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  AC97_EVNT (struct au1xpsc_audio_data*) ; 
 unsigned short AC97_RW_RETRIES ; 
 int PSC_AC97CDC_INDX (unsigned short) ; 
 int PSC_AC97CDC_RD ; 
 int PSC_AC97EVNT_CD ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 struct au1xpsc_audio_data* ac97_to_pscdata (struct snd_ac97*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static unsigned short au1xpsc_ac97_read(struct snd_ac97 *ac97,
					unsigned short reg)
{
	struct au1xpsc_audio_data *pscdata = ac97_to_pscdata(ac97);
	unsigned short retry, tmo;
	unsigned long data;

	__raw_writel(PSC_AC97EVNT_CD, AC97_EVNT(pscdata));
	wmb(); /* drain writebuffer */

	retry = AC97_RW_RETRIES;
	do {
		mutex_lock(&pscdata->lock);

		__raw_writel(PSC_AC97CDC_RD | PSC_AC97CDC_INDX(reg),
			  AC97_CDC(pscdata));
		wmb(); /* drain writebuffer */

		tmo = 20;
		do {
			udelay(21);
			if (__raw_readl(AC97_EVNT(pscdata)) & PSC_AC97EVNT_CD)
				break;
		} while (--tmo);

		data = __raw_readl(AC97_CDC(pscdata));

		__raw_writel(PSC_AC97EVNT_CD, AC97_EVNT(pscdata));
		wmb(); /* drain writebuffer */

		mutex_unlock(&pscdata->lock);

		if (reg != ((data >> 16) & 0x7f))
			tmo = 1;	/* wrong register, try again */

	} while (--retry && !tmo);

	return retry ? data & 0xffff : 0xffff;
}