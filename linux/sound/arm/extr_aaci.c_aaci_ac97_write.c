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
typedef  int u32 ;
struct snd_ac97 {int num; struct aaci* private_data; } ;
struct aaci {int /*<<< orphan*/  ac97_sem; TYPE_1__* dev; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AACI_SL1TX ; 
 scalar_t__ AACI_SL2TX ; 
 scalar_t__ AACI_SLFR ; 
 int FRAME_PERIOD_US ; 
 int SLFR_1TXB ; 
 int SLFR_2TXB ; 
 int /*<<< orphan*/  aaci_ac97_select_codec (struct aaci*,struct snd_ac97*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (unsigned short,scalar_t__) ; 

__attribute__((used)) static void aaci_ac97_write(struct snd_ac97 *ac97, unsigned short reg,
			    unsigned short val)
{
	struct aaci *aaci = ac97->private_data;
	int timeout;
	u32 v;

	if (ac97->num >= 4)
		return;

	mutex_lock(&aaci->ac97_sem);

	aaci_ac97_select_codec(aaci, ac97);

	/*
	 * P54: You must ensure that AACI_SL2TX is always written
	 * to, if required, before data is written to AACI_SL1TX.
	 */
	writel(val << 4, aaci->base + AACI_SL2TX);
	writel(reg << 12, aaci->base + AACI_SL1TX);

	/* Initially, wait one frame period */
	udelay(FRAME_PERIOD_US);

	/* And then wait an additional eight frame periods for it to be sent */
	timeout = FRAME_PERIOD_US * 8;
	do {
		udelay(1);
		v = readl(aaci->base + AACI_SLFR);
	} while ((v & (SLFR_1TXB|SLFR_2TXB)) && --timeout);

	if (v & (SLFR_1TXB|SLFR_2TXB))
		dev_err(&aaci->dev->dev,
			"timeout waiting for write to complete\n");

	mutex_unlock(&aaci->ac97_sem);
}