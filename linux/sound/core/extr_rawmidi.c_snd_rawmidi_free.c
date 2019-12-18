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
struct snd_rawmidi {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* private_free ) (struct snd_rawmidi*) ;int /*<<< orphan*/ * streams; TYPE_1__* ops; int /*<<< orphan*/ * proc_entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dev_unregister ) (struct snd_rawmidi*) ;} ;

/* Variables and functions */
 size_t SNDRV_RAWMIDI_STREAM_INPUT ; 
 size_t SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 
 int /*<<< orphan*/  snd_info_free_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_rawmidi_free_substreams (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct snd_rawmidi*) ; 
 int /*<<< orphan*/  stub2 (struct snd_rawmidi*) ; 

__attribute__((used)) static int snd_rawmidi_free(struct snd_rawmidi *rmidi)
{
	if (!rmidi)
		return 0;

	snd_info_free_entry(rmidi->proc_entry);
	rmidi->proc_entry = NULL;
	mutex_lock(&register_mutex);
	if (rmidi->ops && rmidi->ops->dev_unregister)
		rmidi->ops->dev_unregister(rmidi);
	mutex_unlock(&register_mutex);

	snd_rawmidi_free_substreams(&rmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT]);
	snd_rawmidi_free_substreams(&rmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT]);
	if (rmidi->private_free)
		rmidi->private_free(rmidi);
	put_device(&rmidi->dev);
	return 0;
}