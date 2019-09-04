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
struct snd_pcm_substream {int dummy; } ;
struct hdac_stream {int /*<<< orphan*/  prepared; } ;
struct hdac_ext_stream {int dummy; } ;
struct hdac_bus {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 struct hdac_bus* get_bus_ctx (struct snd_pcm_substream*) ; 
 struct hdac_ext_stream* get_hdac_ext_stream (struct snd_pcm_substream*) ; 
 struct hdac_stream* hdac_stream (struct hdac_ext_stream*) ; 
 int /*<<< orphan*/  snd_hdac_stream_start (struct hdac_stream*,int) ; 
 int /*<<< orphan*/  snd_hdac_stream_stop (struct hdac_stream*) ; 
 int /*<<< orphan*/  snd_hdac_stream_timecounter_init (struct hdac_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int skl_decoupled_trigger(struct snd_pcm_substream *substream,
		int cmd)
{
	struct hdac_bus *bus = get_bus_ctx(substream);
	struct hdac_ext_stream *stream;
	int start;
	unsigned long cookie;
	struct hdac_stream *hstr;

	stream = get_hdac_ext_stream(substream);
	hstr = hdac_stream(stream);

	if (!hstr->prepared)
		return -EPIPE;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	case SNDRV_PCM_TRIGGER_RESUME:
		start = 1;
		break;

	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_STOP:
		start = 0;
		break;

	default:
		return -EINVAL;
	}

	spin_lock_irqsave(&bus->reg_lock, cookie);

	if (start) {
		snd_hdac_stream_start(hdac_stream(stream), true);
		snd_hdac_stream_timecounter_init(hstr, 0);
	} else {
		snd_hdac_stream_stop(hdac_stream(stream));
	}

	spin_unlock_irqrestore(&bus->reg_lock, cookie);

	return 0;
}