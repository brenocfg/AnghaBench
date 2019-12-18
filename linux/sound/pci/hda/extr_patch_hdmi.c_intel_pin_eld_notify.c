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
struct hda_codec {TYPE_1__* bus; int /*<<< orphan*/  core; int /*<<< orphan*/  card; } ;
struct TYPE_2__ {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 scalar_t__ SNDRV_CTL_POWER_D0 ; 
 int /*<<< orphan*/  check_presence_and_report (struct hda_codec*,int,int) ; 
 int intel_port2pin (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hdac_i915_set_bclk (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_hdac_is_in_pm (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_power_get_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_pin_eld_notify(void *audio_ptr, int port, int pipe)
{
	struct hda_codec *codec = audio_ptr;
	int pin_nid;
	int dev_id = pipe;

	pin_nid = intel_port2pin(codec, port);
	if (!pin_nid)
		return;
	/* skip notification during system suspend (but not in runtime PM);
	 * the state will be updated at resume
	 */
	if (snd_power_get_state(codec->card) != SNDRV_CTL_POWER_D0)
		return;
	/* ditto during suspend/resume process itself */
	if (snd_hdac_is_in_pm(&codec->core))
		return;

	snd_hdac_i915_set_bclk(&codec->bus->core);
	check_presence_and_report(codec, pin_nid, dev_id);
}