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
struct snd_virmidi_dev {int /*<<< orphan*/  filelist_sem; int /*<<< orphan*/  filelist_lock; } ;
struct snd_virmidi {int /*<<< orphan*/  parser; int /*<<< orphan*/  list; } ;
struct snd_rawmidi_substream {TYPE_2__* runtime; TYPE_1__* rmidi; } ;
struct TYPE_4__ {struct snd_virmidi* private_data; } ;
struct TYPE_3__ {struct snd_virmidi_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_virmidi*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_midi_event_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_virmidi_input_close(struct snd_rawmidi_substream *substream)
{
	struct snd_virmidi_dev *rdev = substream->rmidi->private_data;
	struct snd_virmidi *vmidi = substream->runtime->private_data;

	down_write(&rdev->filelist_sem);
	write_lock_irq(&rdev->filelist_lock);
	list_del(&vmidi->list);
	write_unlock_irq(&rdev->filelist_lock);
	up_write(&rdev->filelist_sem);
	snd_midi_event_free(vmidi->parser);
	substream->runtime->private_data = NULL;
	kfree(vmidi);
	return 0;
}