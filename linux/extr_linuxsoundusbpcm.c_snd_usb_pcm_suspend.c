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
struct snd_usb_stream {int /*<<< orphan*/ * substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  UAC3_PD_STATE_D2 ; 
 int snd_usb_pcm_change_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int snd_usb_pcm_suspend(struct snd_usb_stream *as)
{
	int ret;

	ret = snd_usb_pcm_change_state(&as->substream[0], UAC3_PD_STATE_D2);
	if (ret < 0)
		return ret;

	ret = snd_usb_pcm_change_state(&as->substream[1], UAC3_PD_STATE_D2);
	if (ret < 0)
		return ret;

	return 0;
}