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
struct snd_sh_dac {int empty; TYPE_1__* pdata; scalar_t__ processed; int /*<<< orphan*/  data_buffer; int /*<<< orphan*/  buffer_end; int /*<<< orphan*/  buffer_begin; struct snd_pcm_substream* substream; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* start ) (TYPE_1__*) ;} ;

/* Variables and functions */
 struct snd_sh_dac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sh_dac_pcm_hw ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static int snd_sh_dac_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_sh_dac *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;

	runtime->hw = snd_sh_dac_pcm_hw;

	chip->substream = substream;
	chip->buffer_begin = chip->buffer_end = chip->data_buffer;
	chip->processed = 0;
	chip->empty = 1;

	chip->pdata->start(chip->pdata);

	return 0;
}