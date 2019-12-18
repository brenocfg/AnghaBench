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
struct snd_midi_event {int bufsize; int lastcmd; int /*<<< orphan*/  lock; int /*<<< orphan*/  type; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ST_INVALID ; 
 int /*<<< orphan*/  kfree (struct snd_midi_event*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_midi_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int snd_midi_event_new(int bufsize, struct snd_midi_event **rdev)
{
	struct snd_midi_event *dev;

	*rdev = NULL;
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL)
		return -ENOMEM;
	if (bufsize > 0) {
		dev->buf = kmalloc(bufsize, GFP_KERNEL);
		if (dev->buf == NULL) {
			kfree(dev);
			return -ENOMEM;
		}
	}
	dev->bufsize = bufsize;
	dev->lastcmd = 0xff;
	dev->type = ST_INVALID;
	spin_lock_init(&dev->lock);
	*rdev = dev;
	return 0;
}