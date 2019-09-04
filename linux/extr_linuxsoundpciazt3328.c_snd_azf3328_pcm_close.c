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
struct snd_azf3328_codec_data {int /*<<< orphan*/ * substream; } ;
struct TYPE_2__ {struct snd_azf3328_codec_data* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int
snd_azf3328_pcm_close(struct snd_pcm_substream *substream
)
{
	struct snd_azf3328_codec_data *codec =
		substream->runtime->private_data;

	codec->substream = NULL;
	return 0;
}