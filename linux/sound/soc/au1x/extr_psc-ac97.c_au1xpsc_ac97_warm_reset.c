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
struct au1xpsc_audio_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_RST (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  PSC_AC97RST_SNC ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct au1xpsc_audio_data* ac97_to_pscdata (struct snd_ac97*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void au1xpsc_ac97_warm_reset(struct snd_ac97 *ac97)
{
	struct au1xpsc_audio_data *pscdata = ac97_to_pscdata(ac97);

	__raw_writel(PSC_AC97RST_SNC, AC97_RST(pscdata));
	wmb(); /* drain writebuffer */
	msleep(10);
	__raw_writel(0, AC97_RST(pscdata));
	wmb(); /* drain writebuffer */
}