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
typedef  int u32 ;
struct snd_intelhad {int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUD_HDMI_STATUS ; 
 int HDMI_AUDIO_BUFFER_DONE ; 
 int HDMI_AUDIO_UNDERRUN ; 
 int /*<<< orphan*/  had_read_register (struct snd_intelhad*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  had_write_register (struct snd_intelhad*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void had_ack_irqs(struct snd_intelhad *ctx)
{
	u32 status_reg;

	if (!ctx->connected)
		return;
	had_read_register(ctx, AUD_HDMI_STATUS, &status_reg);
	status_reg |= HDMI_AUDIO_BUFFER_DONE | HDMI_AUDIO_UNDERRUN;
	had_write_register(ctx, AUD_HDMI_STATUS, status_reg);
	had_read_register(ctx, AUD_HDMI_STATUS, &status_reg);
}