#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_usb_midi {int /*<<< orphan*/  disc_rwsem; int /*<<< orphan*/  mutex; int /*<<< orphan*/  card; struct snd_kcontrol* roland_load_ctl; scalar_t__* opened; int /*<<< orphan*/  list; scalar_t__ disconnected; } ;
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct snd_kcontrol {int /*<<< orphan*/  id; TYPE_2__* vd; } ;
struct TYPE_4__ {int /*<<< orphan*/  access; } ;
struct TYPE_3__ {struct snd_usb_midi* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_INACTIVE ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_INFO ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_usbmidi_input_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_usbmidi_input_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_roland_altsetting (struct snd_usb_midi*) ; 

__attribute__((used)) static int substream_open(struct snd_rawmidi_substream *substream, int dir,
			  int open)
{
	struct snd_usb_midi *umidi = substream->rmidi->private_data;
	struct snd_kcontrol *ctl;

	down_read(&umidi->disc_rwsem);
	if (umidi->disconnected) {
		up_read(&umidi->disc_rwsem);
		return open ? -ENODEV : 0;
	}

	mutex_lock(&umidi->mutex);
	if (open) {
		if (!umidi->opened[0] && !umidi->opened[1]) {
			if (umidi->roland_load_ctl) {
				ctl = umidi->roland_load_ctl;
				ctl->vd[0].access |=
					SNDRV_CTL_ELEM_ACCESS_INACTIVE;
				snd_ctl_notify(umidi->card,
				       SNDRV_CTL_EVENT_MASK_INFO, &ctl->id);
				update_roland_altsetting(umidi);
			}
		}
		umidi->opened[dir]++;
		if (umidi->opened[1])
			snd_usbmidi_input_start(&umidi->list);
	} else {
		umidi->opened[dir]--;
		if (!umidi->opened[1])
			snd_usbmidi_input_stop(&umidi->list);
		if (!umidi->opened[0] && !umidi->opened[1]) {
			if (umidi->roland_load_ctl) {
				ctl = umidi->roland_load_ctl;
				ctl->vd[0].access &=
					~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
				snd_ctl_notify(umidi->card,
				       SNDRV_CTL_EVENT_MASK_INFO, &ctl->id);
			}
		}
	}
	mutex_unlock(&umidi->mutex);
	up_read(&umidi->disc_rwsem);
	return 0;
}