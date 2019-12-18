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
struct snd_sh_dac {TYPE_2__* pdata; int /*<<< orphan*/  data_buffer; int /*<<< orphan*/  buffer_size; TYPE_1__* substream; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  buffer_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  buffer_size; } ;
struct TYPE_3__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_sh_dac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_sh_dac_pcm_prepare(struct snd_pcm_substream *substream)
{
	struct snd_sh_dac *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = chip->substream->runtime;

	chip->buffer_size = runtime->buffer_size;
	memset(chip->data_buffer, 0, chip->pdata->buffer_size);

	return 0;
}