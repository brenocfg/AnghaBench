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
struct snd_emu10k1 {int /*<<< orphan*/  ctl_efx_attn; int /*<<< orphan*/  ctl_efx_send_volume; int /*<<< orphan*/  ctl_efx_send_routing; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_emu10k1_pcm_mixer_notify1 (struct snd_emu10k1*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void snd_emu10k1_pcm_efx_mixer_notify(struct snd_emu10k1 *emu, int idx, int activate)
{
	snd_emu10k1_pcm_mixer_notify1(emu, emu->ctl_efx_send_routing, idx, activate);
	snd_emu10k1_pcm_mixer_notify1(emu, emu->ctl_efx_send_volume, idx, activate);
	snd_emu10k1_pcm_mixer_notify1(emu, emu->ctl_efx_attn, idx, activate);
}