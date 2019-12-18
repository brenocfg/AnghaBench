#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct snd_kcontrol {TYPE_3__ id; } ;
struct TYPE_9__ {TYPE_2__* methods; } ;
struct layout_dev {int have_headphone_detect; int have_lineout_detect; int /*<<< orphan*/  selfptr_lineout; int /*<<< orphan*/  selfptr_headphone; struct snd_kcontrol* lineout_detected_ctrl; TYPE_4__ gpio; struct snd_kcontrol* lineout_ctrl; struct snd_kcontrol* headphone_detected_ctrl; struct snd_kcontrol* headphone_ctrl; struct snd_kcontrol* speaker_ctrl; struct snd_kcontrol* master_ctrl; TYPE_1__* methods; } ;
struct codec_connection {int connected; } ;
struct aoa_codec {struct layout_dev* gpio; struct codec_connection* fabric_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_notify ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_lineout ) (struct layout_dev*,int) ;int /*<<< orphan*/  (* set_headphone ) (struct layout_dev*,int) ;int /*<<< orphan*/  (* set_speakers ) (struct layout_dev*,int) ;} ;
struct TYPE_6__ {int (* get_detect ) (struct layout_dev*,int /*<<< orphan*/ ) ;scalar_t__ set_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOA_NOTIFY_HEADPHONE ; 
 int /*<<< orphan*/  AOA_NOTIFY_LINE_OUT ; 
 int CC_HEADPHONE ; 
 int CC_LINEOUT ; 
 int CC_LINEOUT_LABELLED_HEADPHONE ; 
 int CC_SPEAKERS ; 
 int /*<<< orphan*/  aoa_snd_ctl_add (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  headphone_ctl ; 
 int /*<<< orphan*/  headphone_detect_choice ; 
 int /*<<< orphan*/  headphone_detected ; 
 struct layout_dev* layout_device ; 
 int /*<<< orphan*/  layout_notify (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lineout_ctl ; 
 int /*<<< orphan*/  lineout_detect_choice ; 
 int /*<<< orphan*/  lineout_detected ; 
 int /*<<< orphan*/  master_ctl ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct layout_dev*) ; 
 int /*<<< orphan*/  speakers_ctl ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct layout_dev*,int /*<<< orphan*/ ) ; 
 int stub2 (struct layout_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct layout_dev*,int) ; 
 int /*<<< orphan*/  stub4 (struct layout_dev*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (struct layout_dev*,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 

__attribute__((used)) static void layout_attached_codec(struct aoa_codec *codec)
{
	struct codec_connection *cc;
	struct snd_kcontrol *ctl;
	int headphones, lineout;
	struct layout_dev *ldev = layout_device;

	/* need to add this codec to our codec array! */

	cc = codec->fabric_data;

	headphones = codec->gpio->methods->get_detect(codec->gpio,
						      AOA_NOTIFY_HEADPHONE);
 	lineout = codec->gpio->methods->get_detect(codec->gpio,
						   AOA_NOTIFY_LINE_OUT);

	if (codec->gpio->methods->set_master) {
		ctl = snd_ctl_new1(&master_ctl, codec->gpio);
		ldev->master_ctrl = ctl;
		aoa_snd_ctl_add(ctl);
	}
	while (cc->connected) {
		if (cc->connected & CC_SPEAKERS) {
			if (headphones <= 0 && lineout <= 0)
				ldev->gpio.methods->set_speakers(codec->gpio, 1);
			ctl = snd_ctl_new1(&speakers_ctl, codec->gpio);
			ldev->speaker_ctrl = ctl;
			aoa_snd_ctl_add(ctl);
		}
		if (cc->connected & CC_HEADPHONE) {
			if (headphones == 1)
				ldev->gpio.methods->set_headphone(codec->gpio, 1);
			ctl = snd_ctl_new1(&headphone_ctl, codec->gpio);
			ldev->headphone_ctrl = ctl;
			aoa_snd_ctl_add(ctl);
			ldev->have_headphone_detect =
				!ldev->gpio.methods
					->set_notify(&ldev->gpio,
						     AOA_NOTIFY_HEADPHONE,
						     layout_notify,
						     &ldev->selfptr_headphone);
			if (ldev->have_headphone_detect) {
				ctl = snd_ctl_new1(&headphone_detect_choice,
						   ldev);
				aoa_snd_ctl_add(ctl);
				ctl = snd_ctl_new1(&headphone_detected,
						   ldev);
				ldev->headphone_detected_ctrl = ctl;
				aoa_snd_ctl_add(ctl);
			}
		}
		if (cc->connected & CC_LINEOUT) {
			if (lineout == 1)
				ldev->gpio.methods->set_lineout(codec->gpio, 1);
			ctl = snd_ctl_new1(&lineout_ctl, codec->gpio);
			if (cc->connected & CC_LINEOUT_LABELLED_HEADPHONE)
				strlcpy(ctl->id.name,
					"Headphone Switch", sizeof(ctl->id.name));
			ldev->lineout_ctrl = ctl;
			aoa_snd_ctl_add(ctl);
			ldev->have_lineout_detect =
				!ldev->gpio.methods
					->set_notify(&ldev->gpio,
						     AOA_NOTIFY_LINE_OUT,
						     layout_notify,
						     &ldev->selfptr_lineout);
			if (ldev->have_lineout_detect) {
				ctl = snd_ctl_new1(&lineout_detect_choice,
						   ldev);
				if (cc->connected & CC_LINEOUT_LABELLED_HEADPHONE)
					strlcpy(ctl->id.name,
						"Headphone Detect Autoswitch",
						sizeof(ctl->id.name));
				aoa_snd_ctl_add(ctl);
				ctl = snd_ctl_new1(&lineout_detected,
						   ldev);
				if (cc->connected & CC_LINEOUT_LABELLED_HEADPHONE)
					strlcpy(ctl->id.name,
						"Headphone Detected",
						sizeof(ctl->id.name));
				ldev->lineout_detected_ctrl = ctl;
				aoa_snd_ctl_add(ctl);
			}
		}
		cc++;
	}
	/* now update initial state */
	if (ldev->have_headphone_detect)
		layout_notify(&ldev->selfptr_headphone);
	if (ldev->have_lineout_detect)
		layout_notify(&ldev->selfptr_lineout);
}