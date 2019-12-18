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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_als300_substream_data* private_data; int /*<<< orphan*/  hw; } ;
struct snd_als300_substream_data {int /*<<< orphan*/  block_counter_register; int /*<<< orphan*/  control_register; } ;
struct snd_als300 {struct snd_pcm_substream* capture_substream; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RECORD_BLOCK_COUNTER ; 
 int /*<<< orphan*/  RECORD_CONTROL ; 
 struct snd_als300_substream_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_als300_capture_hw ; 
 struct snd_als300* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_als300_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_als300 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_als300_substream_data *data = kzalloc(sizeof(*data),
								GFP_KERNEL);

	if (!data)
		return -ENOMEM;
	chip->capture_substream = substream;
	runtime->hw = snd_als300_capture_hw;
	runtime->private_data = data;
	data->control_register = RECORD_CONTROL;
	data->block_counter_register = RECORD_BLOCK_COUNTER;
	return 0;
}