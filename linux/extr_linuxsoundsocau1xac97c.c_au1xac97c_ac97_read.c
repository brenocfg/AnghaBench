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
 int /*<<< orphan*/  AC97_CMDRESP ; 
 unsigned int AC97_RW_RETRIES ; 
 int /*<<< orphan*/  AC97_STATUS ; 
 int CMD_IDX (unsigned short) ; 
 int CMD_READ ; 
 unsigned long RD (struct au1xpsc_audio_data*,int /*<<< orphan*/ ) ; 
 unsigned long STAT_CP ; 
 int /*<<< orphan*/  WR (struct au1xpsc_audio_data*,int /*<<< orphan*/ ,int) ; 
 struct au1xpsc_audio_data* ac97_to_ctx (struct snd_ac97*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned short au1xac97c_ac97_read(struct snd_ac97 *ac97,
					  unsigned short r)
{
	struct au1xpsc_audio_data *ctx = ac97_to_ctx(ac97);
	unsigned int tmo, retry;
	unsigned long data;

	data = ~0;
	retry = AC97_RW_RETRIES;
	do {
		mutex_lock(&ctx->lock);

		tmo = 6;
		while ((RD(ctx, AC97_STATUS) & STAT_CP) && --tmo)
			udelay(21);	/* wait an ac97 frame time */
		if (!tmo) {
			pr_debug("ac97rd timeout #1\n");
			goto next;
		}

		WR(ctx, AC97_CMDRESP, CMD_IDX(r) | CMD_READ);

		/* stupid errata: data is only valid for 21us, so
		 * poll, Forrest, poll...
		 */
		tmo = 0x10000;
		while ((RD(ctx, AC97_STATUS) & STAT_CP) && --tmo)
			asm volatile ("nop");
		data = RD(ctx, AC97_CMDRESP);

		if (!tmo)
			pr_debug("ac97rd timeout #2\n");

next:
		mutex_unlock(&ctx->lock);
	} while (--retry && !tmo);

	pr_debug("AC97RD %04x %04lx %d\n", r, data, retry);

	return retry ? data & 0xffff : 0xffff;
}