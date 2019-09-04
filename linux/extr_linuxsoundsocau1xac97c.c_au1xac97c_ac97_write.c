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
 int CMD_SET_DATA (unsigned short) ; 
 int CMD_WRITE ; 
 int RD (struct au1xpsc_audio_data*,int /*<<< orphan*/ ) ; 
 int STAT_CP ; 
 int /*<<< orphan*/  WR (struct au1xpsc_audio_data*,int /*<<< orphan*/ ,int) ; 
 struct au1xpsc_audio_data* ac97_to_ctx (struct snd_ac97*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void au1xac97c_ac97_write(struct snd_ac97 *ac97, unsigned short r,
				 unsigned short v)
{
	struct au1xpsc_audio_data *ctx = ac97_to_ctx(ac97);
	unsigned int tmo, retry;

	retry = AC97_RW_RETRIES;
	do {
		mutex_lock(&ctx->lock);

		for (tmo = 5; (RD(ctx, AC97_STATUS) & STAT_CP) && tmo; tmo--)
			udelay(21);
		if (!tmo) {
			pr_debug("ac97wr timeout #1\n");
			goto next;
		}

		WR(ctx, AC97_CMDRESP, CMD_WRITE | CMD_IDX(r) | CMD_SET_DATA(v));

		for (tmo = 10; (RD(ctx, AC97_STATUS) & STAT_CP) && tmo; tmo--)
			udelay(21);
		if (!tmo)
			pr_debug("ac97wr timeout #2\n");
next:
		mutex_unlock(&ctx->lock);
	} while (--retry && !tmo);

	pr_debug("AC97WR %04x %04x %d\n", r, v, retry);
}