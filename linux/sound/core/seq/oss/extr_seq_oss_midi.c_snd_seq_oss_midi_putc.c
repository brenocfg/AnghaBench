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
struct snd_seq_event {int dummy; } ;
struct seq_oss_midi {int /*<<< orphan*/  use_lock; int /*<<< orphan*/  port; int /*<<< orphan*/  client; int /*<<< orphan*/  coder; } ;
struct seq_oss_devinfo {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct seq_oss_midi* get_mididev (struct seq_oss_devinfo*,int) ; 
 scalar_t__ snd_midi_event_encode_byte (int /*<<< orphan*/ ,unsigned char,struct snd_seq_event*) ; 
 int /*<<< orphan*/  snd_seq_oss_fill_addr (struct seq_oss_devinfo*,struct snd_seq_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 

int
snd_seq_oss_midi_putc(struct seq_oss_devinfo *dp, int dev, unsigned char c, struct snd_seq_event *ev)
{
	struct seq_oss_midi *mdev;

	if ((mdev = get_mididev(dp, dev)) == NULL)
		return -ENODEV;
	if (snd_midi_event_encode_byte(mdev->coder, c, ev)) {
		snd_seq_oss_fill_addr(dp, ev, mdev->client, mdev->port);
		snd_use_lock_free(&mdev->use_lock);
		return 0;
	}
	snd_use_lock_free(&mdev->use_lock);
	return -EINVAL;
}