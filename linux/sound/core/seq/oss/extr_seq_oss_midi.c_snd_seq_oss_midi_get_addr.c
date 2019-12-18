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
struct snd_seq_addr {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct seq_oss_midi {int /*<<< orphan*/  use_lock; int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct seq_oss_devinfo {int dummy; } ;

/* Variables and functions */
 struct seq_oss_midi* get_mididev (struct seq_oss_devinfo*,int) ; 
 int /*<<< orphan*/  snd_use_lock_free (int /*<<< orphan*/ *) ; 

void
snd_seq_oss_midi_get_addr(struct seq_oss_devinfo *dp, int dev, struct snd_seq_addr *addr)
{
	struct seq_oss_midi *mdev;

	if ((mdev = get_mididev(dp, dev)) == NULL)
		return;
	addr->client = mdev->client;
	addr->port = mdev->port;
	snd_use_lock_free(&mdev->use_lock);
}