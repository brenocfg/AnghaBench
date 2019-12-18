#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_rawmidi_substream {size_t stream; int /*<<< orphan*/ * pid; scalar_t__ append; scalar_t__ opened; TYPE_2__* runtime; TYPE_1__* ops; scalar_t__ active_sensing; scalar_t__ use_count; } ;
struct snd_rawmidi {TYPE_3__* streams; } ;
struct TYPE_6__ {int /*<<< orphan*/  substream_opened; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* private_free ) (struct snd_rawmidi_substream*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* close ) (struct snd_rawmidi_substream*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ERESTARTSYS ; 
 size_t SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_rawmidi_drain_output (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  snd_rawmidi_input_trigger (struct snd_rawmidi_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_kernel_write (struct snd_rawmidi_substream*,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_rawmidi_output_trigger (struct snd_rawmidi_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_runtime_free (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  stub1 (struct snd_rawmidi_substream*) ; 
 int /*<<< orphan*/  stub2 (struct snd_rawmidi_substream*) ; 

__attribute__((used)) static void close_substream(struct snd_rawmidi *rmidi,
			    struct snd_rawmidi_substream *substream,
			    int cleanup)
{
	if (--substream->use_count)
		return;

	if (cleanup) {
		if (substream->stream == SNDRV_RAWMIDI_STREAM_INPUT)
			snd_rawmidi_input_trigger(substream, 0);
		else {
			if (substream->active_sensing) {
				unsigned char buf = 0xfe;
				/* sending single active sensing message
				 * to shut the device up
				 */
				snd_rawmidi_kernel_write(substream, &buf, 1);
			}
			if (snd_rawmidi_drain_output(substream) == -ERESTARTSYS)
				snd_rawmidi_output_trigger(substream, 0);
		}
	}
	substream->ops->close(substream);
	if (substream->runtime->private_free)
		substream->runtime->private_free(substream);
	snd_rawmidi_runtime_free(substream);
	substream->opened = 0;
	substream->append = 0;
	put_pid(substream->pid);
	substream->pid = NULL;
	rmidi->streams[substream->stream].substream_opened--;
}