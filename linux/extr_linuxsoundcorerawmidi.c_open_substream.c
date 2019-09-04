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
struct snd_rawmidi_substream {scalar_t__ use_count; int opened; int append; size_t stream; int /*<<< orphan*/  pid; scalar_t__ active_sensing; TYPE_1__* ops; } ;
struct snd_rawmidi {TYPE_2__* streams; } ;
struct TYPE_4__ {int /*<<< orphan*/  substream_opened; } ;
struct TYPE_3__ {int (* open ) (struct snd_rawmidi_substream*) ;} ;

/* Variables and functions */
 int SNDRV_RAWMIDI_LFLG_APPEND ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 int snd_rawmidi_runtime_create (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  snd_rawmidi_runtime_free (struct snd_rawmidi_substream*) ; 
 int stub1 (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_substream(struct snd_rawmidi *rmidi,
			  struct snd_rawmidi_substream *substream,
			  int mode)
{
	int err;

	if (substream->use_count == 0) {
		err = snd_rawmidi_runtime_create(substream);
		if (err < 0)
			return err;
		err = substream->ops->open(substream);
		if (err < 0) {
			snd_rawmidi_runtime_free(substream);
			return err;
		}
		substream->opened = 1;
		substream->active_sensing = 0;
		if (mode & SNDRV_RAWMIDI_LFLG_APPEND)
			substream->append = 1;
		substream->pid = get_pid(task_pid(current));
		rmidi->streams[substream->stream].substream_opened++;
	}
	substream->use_count++;
	return 0;
}