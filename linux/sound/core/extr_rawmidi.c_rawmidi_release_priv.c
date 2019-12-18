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
struct snd_rawmidi_file {struct snd_rawmidi* rmidi; int /*<<< orphan*/ * output; int /*<<< orphan*/ * input; } ;
struct snd_rawmidi {int /*<<< orphan*/  open_wait; int /*<<< orphan*/  open_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_substream (struct snd_rawmidi*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rawmidi_release_priv(struct snd_rawmidi_file *rfile)
{
	struct snd_rawmidi *rmidi;

	rmidi = rfile->rmidi;
	mutex_lock(&rmidi->open_mutex);
	if (rfile->input) {
		close_substream(rmidi, rfile->input, 1);
		rfile->input = NULL;
	}
	if (rfile->output) {
		close_substream(rmidi, rfile->output, 1);
		rfile->output = NULL;
	}
	rfile->rmidi = NULL;
	mutex_unlock(&rmidi->open_mutex);
	wake_up(&rmidi->open_wait);
}