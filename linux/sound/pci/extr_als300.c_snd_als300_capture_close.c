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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_als300_substream_data {int dummy; } ;
struct snd_als300 {int /*<<< orphan*/ * capture_substream; } ;
struct TYPE_2__ {struct snd_als300_substream_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_als300_substream_data*) ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_als300* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_als300_capture_close(struct snd_pcm_substream *substream)
{
	struct snd_als300 *chip = snd_pcm_substream_chip(substream);
	struct snd_als300_substream_data *data;

	data = substream->runtime->private_data;
	kfree(data);
	chip->capture_substream = NULL;
	snd_pcm_lib_free_pages(substream);
	return 0;
}