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
struct au1xpsc_audio_data {int cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CONFIG ; 
 int CFG_SG ; 
 int CFG_SN ; 
 int /*<<< orphan*/  WR (struct au1xpsc_audio_data*,int /*<<< orphan*/ ,int) ; 
 struct au1xpsc_audio_data* ac97_to_ctx (struct snd_ac97*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void au1xac97c_ac97_warm_reset(struct snd_ac97 *ac97)
{
	struct au1xpsc_audio_data *ctx = ac97_to_ctx(ac97);

	WR(ctx, AC97_CONFIG, ctx->cfg | CFG_SG | CFG_SN);
	msleep(20);
	WR(ctx, AC97_CONFIG, ctx->cfg | CFG_SG);
	WR(ctx, AC97_CONFIG, ctx->cfg);
}