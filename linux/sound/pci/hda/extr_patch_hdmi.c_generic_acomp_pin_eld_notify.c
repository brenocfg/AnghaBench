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
struct hdmi_spec {int /*<<< orphan*/  (* port2pin ) (struct hda_codec*,int) ;} ;
struct hda_codec {int /*<<< orphan*/  core; int /*<<< orphan*/  card; struct hdmi_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 scalar_t__ AC_WID_PIN ; 
 scalar_t__ SNDRV_CTL_POWER_D0 ; 
 int /*<<< orphan*/  check_presence_and_report (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_wcaps_type (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_hdac_is_in_pm (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_power_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hda_codec*,int) ; 

__attribute__((used)) static void generic_acomp_pin_eld_notify(void *audio_ptr, int port, int dev_id)
{
	struct hda_codec *codec = audio_ptr;
	struct hdmi_spec *spec = codec->spec;
	hda_nid_t pin_nid = spec->port2pin(codec, port);

	if (!pin_nid)
		return;
	if (get_wcaps_type(get_wcaps(codec, pin_nid)) != AC_WID_PIN)
		return;
	/* skip notification during system suspend (but not in runtime PM);
	 * the state will be updated at resume
	 */
	if (snd_power_get_state(codec->card) != SNDRV_CTL_POWER_D0)
		return;
	/* ditto during suspend/resume process itself */
	if (snd_hdac_is_in_pm(&codec->core))
		return;

	check_presence_and_report(codec, pin_nid, dev_id);
}