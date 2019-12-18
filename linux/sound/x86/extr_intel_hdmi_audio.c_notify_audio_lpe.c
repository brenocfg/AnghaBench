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
struct snd_intelhad_card {struct snd_intelhad* pcm_ctx; } ;
struct snd_intelhad {int port; int /*<<< orphan*/  hdmi_audio_wq; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct snd_intelhad_card* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ single_port ; 

__attribute__((used)) static void notify_audio_lpe(struct platform_device *pdev, int port)
{
	struct snd_intelhad_card *card_ctx = platform_get_drvdata(pdev);
	struct snd_intelhad *ctx;

	ctx = &card_ctx->pcm_ctx[single_port ? 0 : port];
	if (single_port)
		ctx->port = port;

	schedule_work(&ctx->hdmi_audio_wq);
}