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
struct snd_rawmidi_substream {scalar_t__ stream; struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {int avail_min; scalar_t__ hw_ptr; scalar_t__ appl_ptr; int /*<<< orphan*/  buffer; scalar_t__ buffer_size; scalar_t__ avail; int /*<<< orphan*/ * event; int /*<<< orphan*/  event_work; int /*<<< orphan*/  sleep; int /*<<< orphan*/  lock; struct snd_rawmidi_substream* substream; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ SNDRV_RAWMIDI_STREAM_INPUT ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_rawmidi_runtime*) ; 
 int /*<<< orphan*/  kvzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct snd_rawmidi_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_rawmidi_input_event_work ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_rawmidi_runtime_create(struct snd_rawmidi_substream *substream)
{
	struct snd_rawmidi_runtime *runtime;

	runtime = kzalloc(sizeof(*runtime), GFP_KERNEL);
	if (!runtime)
		return -ENOMEM;
	runtime->substream = substream;
	spin_lock_init(&runtime->lock);
	init_waitqueue_head(&runtime->sleep);
	INIT_WORK(&runtime->event_work, snd_rawmidi_input_event_work);
	runtime->event = NULL;
	runtime->buffer_size = PAGE_SIZE;
	runtime->avail_min = 1;
	if (substream->stream == SNDRV_RAWMIDI_STREAM_INPUT)
		runtime->avail = 0;
	else
		runtime->avail = runtime->buffer_size;
	runtime->buffer = kvzalloc(runtime->buffer_size, GFP_KERNEL);
	if (!runtime->buffer) {
		kfree(runtime);
		return -ENOMEM;
	}
	runtime->appl_ptr = runtime->hw_ptr = 0;
	substream->runtime = runtime;
	return 0;
}