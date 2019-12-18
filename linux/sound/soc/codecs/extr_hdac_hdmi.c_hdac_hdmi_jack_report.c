#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hdac_hdmi_port {int is_connect; TYPE_1__* pin; } ;
struct hdac_hdmi_pcm {int jack_event; int /*<<< orphan*/  jack; int /*<<< orphan*/  pcm_id; } ;
struct hdac_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct hdac_device* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_JACK_AVOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdac_hdmi_jack_report(struct hdac_hdmi_pcm *pcm,
		struct hdac_hdmi_port *port, bool is_connect)
{
	struct hdac_device *hdev = port->pin->hdev;

	port->is_connect = is_connect;
	if (is_connect) {
		/*
		 * Report Jack connect event when a device is connected
		 * for the first time where same PCM is attached to multiple
		 * ports.
		 */
		if (pcm->jack_event == 0) {
			dev_dbg(&hdev->dev,
					"jack report for pcm=%d\n",
					pcm->pcm_id);
			snd_soc_jack_report(pcm->jack, SND_JACK_AVOUT,
						SND_JACK_AVOUT);
		}
		pcm->jack_event++;
	} else {
		/*
		 * Report Jack disconnect event when a device is disconnected
		 * is the only last connected device when same PCM is attached
		 * to multiple ports.
		 */
		if (pcm->jack_event == 1)
			snd_soc_jack_report(pcm->jack, 0, SND_JACK_AVOUT);
		if (pcm->jack_event > 0)
			pcm->jack_event--;
	}
}