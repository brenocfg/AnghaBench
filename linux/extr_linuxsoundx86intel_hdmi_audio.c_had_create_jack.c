#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm {int device; } ;
struct snd_intelhad {TYPE_2__* jack; TYPE_1__* card_ctx; } ;
typedef  int /*<<< orphan*/  hdmi_str ;
struct TYPE_4__ {struct snd_intelhad* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_JACK_AVOUT ; 
 int snd_jack_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__**,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int had_create_jack(struct snd_intelhad *ctx,
			   struct snd_pcm *pcm)
{
	char hdmi_str[32];
	int err;

	snprintf(hdmi_str, sizeof(hdmi_str),
		 "HDMI/DP,pcm=%d", pcm->device);

	err = snd_jack_new(ctx->card_ctx->card, hdmi_str,
			   SND_JACK_AVOUT, &ctx->jack,
			   true, false);
	if (err < 0)
		return err;
	ctx->jack->private_data = ctx;
	return 0;
}