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
union cmdret {int* retlongs; } ;
struct snd_riptide {struct cmdif* cif; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int period_size; } ;
struct pcmhw {int size; int pointer; int /*<<< orphan*/  id; } ;
struct cmdif {int dummy; } ;
typedef  int snd_pcm_uframes_t ;

/* Variables and functions */
 union cmdret CMDRET_ZERO ; 
 int /*<<< orphan*/  SEND_GPOS (struct cmdif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union cmdret*) ; 
 int bytes_to_frames (struct snd_pcm_runtime*,int) ; 
 struct pcmhw* get_pcmhwdev (struct snd_pcm_substream*) ; 
 struct snd_riptide* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_printdd (char*,int,int,...) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_riptide_pointer(struct snd_pcm_substream
					     *substream)
{
	struct snd_riptide *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct pcmhw *data = get_pcmhwdev(substream);
	struct cmdif *cif = chip->cif;
	union cmdret rptr = CMDRET_ZERO;
	snd_pcm_uframes_t ret;

	SEND_GPOS(cif, 0, data->id, &rptr);
	if (data->size && runtime->period_size) {
		snd_printdd
		    ("pointer stream %d position 0x%x(0x%x in buffer) bytes 0x%lx(0x%lx in period) frames\n",
		     data->id, rptr.retlongs[1], rptr.retlongs[1] % data->size,
		     bytes_to_frames(runtime, rptr.retlongs[1]),
		     bytes_to_frames(runtime,
				     rptr.retlongs[1]) % runtime->period_size);
		if (rptr.retlongs[1] > data->pointer)
			ret =
			    bytes_to_frames(runtime,
					    rptr.retlongs[1] % data->size);
		else
			ret =
			    bytes_to_frames(runtime,
					    data->pointer % data->size);
	} else {
		snd_printdd("stream not started or strange parms (%d %ld)\n",
			    data->size, runtime->period_size);
		ret = bytes_to_frames(runtime, 0);
	}
	return ret;
}