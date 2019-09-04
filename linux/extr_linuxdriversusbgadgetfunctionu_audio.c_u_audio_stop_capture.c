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
struct snd_uac_chip {int /*<<< orphan*/  c_prm; } ;
struct g_audio {int /*<<< orphan*/  out_ep; struct snd_uac_chip* uac; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_ep (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void u_audio_stop_capture(struct g_audio *audio_dev)
{
	struct snd_uac_chip *uac = audio_dev->uac;

	free_ep(&uac->c_prm, audio_dev->out_ep);
}