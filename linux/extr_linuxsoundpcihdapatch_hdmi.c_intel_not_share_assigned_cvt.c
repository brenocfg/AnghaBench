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
struct hdmi_spec_per_pin {scalar_t__ pin_nid; int dev_id; int /*<<< orphan*/  pcm; } ;
struct hdmi_spec_per_cvt {int /*<<< orphan*/  assigned; } ;
struct hdmi_spec {int num_pins; int num_cvts; } ;
struct hda_codec {struct hdmi_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_CONNECT_SEL ; 
 int /*<<< orphan*/  AC_VERB_SET_CONNECT_SEL ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*,int,scalar_t__) ; 
 struct hdmi_spec_per_cvt* get_cvt (struct hdmi_spec*,int) ; 
 struct hdmi_spec_per_pin* get_pin (struct hdmi_spec*,int) ; 
 int snd_hda_codec_read (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_get_dev_select (struct hda_codec*,scalar_t__) ; 
 int snd_hda_get_num_devices (struct hda_codec*,scalar_t__) ; 
 int /*<<< orphan*/  snd_hda_set_dev_select (struct hda_codec*,scalar_t__,int) ; 

__attribute__((used)) static void intel_not_share_assigned_cvt(struct hda_codec *codec,
					 hda_nid_t pin_nid,
					 int dev_id, int mux_idx)
{
	struct hdmi_spec *spec = codec->spec;
	hda_nid_t nid;
	int cvt_idx, curr;
	struct hdmi_spec_per_cvt *per_cvt;
	struct hdmi_spec_per_pin *per_pin;
	int pin_idx;

	/* configure the pins connections */
	for (pin_idx = 0; pin_idx < spec->num_pins; pin_idx++) {
		int dev_id_saved;
		int dev_num;

		per_pin = get_pin(spec, pin_idx);
		/*
		 * pin not connected to monitor
		 * no need to operate on it
		 */
		if (!per_pin->pcm)
			continue;

		if ((per_pin->pin_nid == pin_nid) &&
			(per_pin->dev_id == dev_id))
			continue;

		/*
		 * if per_pin->dev_id >= dev_num,
		 * snd_hda_get_dev_select() will fail,
		 * and the following operation is unpredictable.
		 * So skip this situation.
		 */
		dev_num = snd_hda_get_num_devices(codec, per_pin->pin_nid) + 1;
		if (per_pin->dev_id >= dev_num)
			continue;

		nid = per_pin->pin_nid;

		/*
		 * Calling this function should not impact
		 * on the device entry selection
		 * So let's save the dev id for each pin,
		 * and restore it when return
		 */
		dev_id_saved = snd_hda_get_dev_select(codec, nid);
		snd_hda_set_dev_select(codec, nid, per_pin->dev_id);
		curr = snd_hda_codec_read(codec, nid, 0,
					  AC_VERB_GET_CONNECT_SEL, 0);
		if (curr != mux_idx) {
			snd_hda_set_dev_select(codec, nid, dev_id_saved);
			continue;
		}


		/* choose an unassigned converter. The conveters in the
		 * connection list are in the same order as in the codec.
		 */
		for (cvt_idx = 0; cvt_idx < spec->num_cvts; cvt_idx++) {
			per_cvt = get_cvt(spec, cvt_idx);
			if (!per_cvt->assigned) {
				codec_dbg(codec,
					  "choose cvt %d for pin nid %d\n",
					cvt_idx, nid);
				snd_hda_codec_write_cache(codec, nid, 0,
					    AC_VERB_SET_CONNECT_SEL,
					    cvt_idx);
				break;
			}
		}
		snd_hda_set_dev_select(codec, nid, dev_id_saved);
	}
}