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
struct hdmi_codec_priv {unsigned int jack_status; scalar_t__ jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_JACK_LINEOUT ; 
 int /*<<< orphan*/  snd_soc_jack_report (scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_codec_jack_report(struct hdmi_codec_priv *hcp,
				   unsigned int jack_status)
{
	if (hcp->jack && jack_status != hcp->jack_status) {
		snd_soc_jack_report(hcp->jack, jack_status, SND_JACK_LINEOUT);
		hcp->jack_status = jack_status;
	}
}