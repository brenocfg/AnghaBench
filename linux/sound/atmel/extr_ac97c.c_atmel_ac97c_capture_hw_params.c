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
struct snd_pcm_hw_params {int dummy; } ;
struct atmel_ac97c {int /*<<< orphan*/  cur_format; int /*<<< orphan*/  cur_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opened_mutex ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct atmel_ac97c* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int atmel_ac97c_capture_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *hw_params)
{
	struct atmel_ac97c *chip = snd_pcm_substream_chip(substream);
	int retval;

	retval = snd_pcm_lib_malloc_pages(substream,
					params_buffer_bytes(hw_params));
	if (retval < 0)
		return retval;

	/* Set restrictions to params. */
	mutex_lock(&opened_mutex);
	chip->cur_rate = params_rate(hw_params);
	chip->cur_format = params_format(hw_params);
	mutex_unlock(&opened_mutex);

	return retval;
}