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
struct snd_jack {struct hdmi_pcm* private_data; } ;
struct hdmi_pcm {int /*<<< orphan*/ * jack; } ;

/* Variables and functions */

__attribute__((used)) static void free_hdmi_jack_priv(struct snd_jack *jack)
{
	struct hdmi_pcm *pcm = jack->private_data;

	pcm->jack = NULL;
}