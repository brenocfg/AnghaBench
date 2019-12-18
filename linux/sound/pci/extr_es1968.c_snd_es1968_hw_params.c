#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dma_bytes; struct esschan* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct esschan {TYPE_3__* memory; } ;
struct es1968 {TYPE_1__* card; } ;
struct TYPE_6__ {int bytes; } ;
struct TYPE_7__ {TYPE_2__ buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_es1968_free_memory (struct es1968*,TYPE_3__*) ; 
 TYPE_3__* snd_es1968_new_memory (struct es1968*,int) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,TYPE_2__*) ; 
 struct es1968* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_es1968_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *hw_params)
{
	struct es1968 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct esschan *chan = runtime->private_data;
	int size = params_buffer_bytes(hw_params);

	if (chan->memory) {
		if (chan->memory->buf.bytes >= size) {
			runtime->dma_bytes = size;
			return 0;
		}
		snd_es1968_free_memory(chip, chan->memory);
	}
	chan->memory = snd_es1968_new_memory(chip, size);
	if (chan->memory == NULL) {
		dev_dbg(chip->card->dev,
			"cannot allocate dma buffer: size = %d\n", size);
		return -ENOMEM;
	}
	snd_pcm_set_runtime_buffer(substream, &chan->memory->buf);
	return 1; /* area was changed */
}